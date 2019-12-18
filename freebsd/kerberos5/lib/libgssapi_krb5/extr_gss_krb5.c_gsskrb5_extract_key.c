#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_keyblock ;
typedef  void* krb5_error_code ;
typedef  int /*<<< orphan*/ * krb5_context ;
typedef  scalar_t__ gss_ctx_id_t ;
typedef  TYPE_2__* gss_buffer_set_t ;
typedef  int /*<<< orphan*/  gss_OID ;
struct TYPE_7__ {int count; TYPE_1__* elements; } ;
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/  value; } ;
typedef  void* OM_uint32 ;

/* Variables and functions */
 void* EINVAL ; 
 void* ENOMEM ; 
 TYPE_2__* GSS_C_NO_BUFFER_SET ; 
 scalar_t__ GSS_C_NO_CONTEXT ; 
 void* GSS_S_COMPLETE ; 
 void* GSS_S_FAILURE ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 void* gss_inquire_sec_context_by_oid (void**,scalar_t__,int /*<<< orphan*/  const,TYPE_2__**) ; 
 int /*<<< orphan*/  gss_release_buffer_set (void**,TYPE_2__**) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_keyblock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* krb5_init_context (int /*<<< orphan*/ **) ; 
 void* krb5_ret_keyblock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OM_uint32
gsskrb5_extract_key(OM_uint32 *minor_status,
		    gss_ctx_id_t context_handle,
		    const gss_OID oid, 
		    krb5_keyblock **keyblock)
{
    krb5_error_code ret;
    gss_buffer_set_t data_set = GSS_C_NO_BUFFER_SET;
    OM_uint32 major_status;
    krb5_context context = NULL;
    krb5_storage *sp = NULL;

    if (context_handle == GSS_C_NO_CONTEXT) {
	ret = EINVAL;
	return GSS_S_FAILURE;
    }
    
    ret = krb5_init_context(&context);
    if(ret) {
	*minor_status = ret;
	return GSS_S_FAILURE;
    }

    major_status =
	gss_inquire_sec_context_by_oid (minor_status,
					context_handle,
					oid,
					&data_set);
    if (major_status)
	return major_status;
    
    if (data_set == GSS_C_NO_BUFFER_SET || data_set->count != 1) {
	gss_release_buffer_set(minor_status, &data_set);
	*minor_status = EINVAL;
	return GSS_S_FAILURE;
    }

    sp = krb5_storage_from_mem(data_set->elements[0].value,
			       data_set->elements[0].length);
    if (sp == NULL) {
	ret = ENOMEM;
	goto out;
    }
    
    *keyblock = calloc(1, sizeof(**keyblock));
    if (keyblock == NULL) {
	ret = ENOMEM;
	goto out;
    }

    ret = krb5_ret_keyblock(sp, *keyblock);

out: 
    gss_release_buffer_set(minor_status, &data_set);
    if (sp)
	krb5_storage_free(sp);
    if (ret && keyblock) {
	krb5_free_keyblock(context, *keyblock);
	*keyblock = NULL;
    }
    if (context)
	krb5_free_context(context);

    *minor_status = ret;
    if (ret)
	return GSS_S_FAILURE;

    return GSS_S_COMPLETE;
}