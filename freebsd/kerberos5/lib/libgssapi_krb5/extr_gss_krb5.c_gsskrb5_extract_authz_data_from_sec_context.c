#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;

/* Type definitions */
struct TYPE_18__ {int length; int* components; } ;
typedef  TYPE_2__ heim_oid ;
typedef  scalar_t__ gss_ctx_id_t ;
typedef  TYPE_3__* gss_buffer_t ;
typedef  TYPE_4__* gss_buffer_set_t ;
struct TYPE_21__ {size_t length; int* elements; } ;
typedef  TYPE_5__ gss_OID_desc ;
struct TYPE_20__ {int count; TYPE_1__* elements; } ;
struct TYPE_19__ {int* value; int length; } ;
struct TYPE_17__ {size_t length; int* value; } ;
struct TYPE_16__ {int /*<<< orphan*/  length; int /*<<< orphan*/  elements; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ENOMEM ; 
 TYPE_4__* GSS_C_NO_BUFFER_SET ; 
 scalar_t__ GSS_C_NO_CONTEXT ; 
 TYPE_14__* GSS_KRB5_EXTRACT_AUTHZ_DATA_FROM_SEC_CONTEXT_X ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  abort () ; 
 int* calloc (int,int) ; 
 int /*<<< orphan*/  der_free_oid (TYPE_2__*) ; 
 scalar_t__ der_get_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 size_t der_length_oid (TYPE_2__*) ; 
 scalar_t__ der_put_oid (unsigned char*,size_t,TYPE_2__*,size_t*) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ gss_inquire_sec_context_by_oid (scalar_t__*,scalar_t__,TYPE_5__*,TYPE_4__**) ; 
 int /*<<< orphan*/  gss_release_buffer_set (scalar_t__*,TYPE_4__**) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

OM_uint32
gsskrb5_extract_authz_data_from_sec_context(OM_uint32 *minor_status,
					    gss_ctx_id_t context_handle,
					    int ad_type,
					    gss_buffer_t ad_data)
{
    gss_buffer_set_t data_set = GSS_C_NO_BUFFER_SET;
    OM_uint32 maj_stat;
    gss_OID_desc oid_flat;
    heim_oid baseoid, oid;
    size_t size;

    if (context_handle == GSS_C_NO_CONTEXT) {
	*minor_status = EINVAL;
	return GSS_S_FAILURE;
    }

    /* All this to append an integer to an oid... */

    if (der_get_oid(GSS_KRB5_EXTRACT_AUTHZ_DATA_FROM_SEC_CONTEXT_X->elements,
		    GSS_KRB5_EXTRACT_AUTHZ_DATA_FROM_SEC_CONTEXT_X->length,
		    &baseoid, NULL) != 0) {
	*minor_status = EINVAL;
	return GSS_S_FAILURE;
    }
    
    oid.length = baseoid.length + 1;
    oid.components = calloc(oid.length, sizeof(*oid.components));
    if (oid.components == NULL) {
	der_free_oid(&baseoid);

	*minor_status = ENOMEM;
	return GSS_S_FAILURE;
    }

    memcpy(oid.components, baseoid.components, 
	   baseoid.length * sizeof(*baseoid.components));
    
    der_free_oid(&baseoid);

    oid.components[oid.length - 1] = ad_type;

    oid_flat.length = der_length_oid(&oid);
    oid_flat.elements = malloc(oid_flat.length);
    if (oid_flat.elements == NULL) {
	free(oid.components);
	*minor_status = ENOMEM;
	return GSS_S_FAILURE;
    }

    if (der_put_oid((unsigned char *)oid_flat.elements + oid_flat.length - 1, 
		    oid_flat.length, &oid, &size) != 0) {
	free(oid.components);
	free(oid_flat.elements);
	*minor_status = EINVAL;
	return GSS_S_FAILURE;
    }
    if (oid_flat.length != size)
	abort();

    free(oid.components);

    /* FINALLY, we have the OID */

    maj_stat = gss_inquire_sec_context_by_oid (minor_status,
					       context_handle,
					       &oid_flat,
					       &data_set);

    free(oid_flat.elements);

    if (maj_stat)
	return maj_stat;
    
    if (data_set == GSS_C_NO_BUFFER_SET || data_set->count != 1) {
	gss_release_buffer_set(minor_status, &data_set);
	*minor_status = EINVAL;
	return GSS_S_FAILURE;
    }

    ad_data->value = malloc(data_set->elements[0].length);
    if (ad_data->value == NULL) {
	gss_release_buffer_set(minor_status, &data_set);
	*minor_status = ENOMEM;
	return GSS_S_FAILURE;
    }

    ad_data->length = data_set->elements[0].length;
    memcpy(ad_data->value, data_set->elements[0].value, ad_data->length);
    gss_release_buffer_set(minor_status, &data_set);
    
    *minor_status = 0;
    return GSS_S_COMPLETE;
}