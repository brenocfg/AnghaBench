#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  scalar_t__ krb5_error_code ;
typedef  scalar_t__ krb5_enctype ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  TYPE_1__* gsskrb5_cred ;
typedef  scalar_t__ gss_cred_id_t ;
typedef  TYPE_2__* gss_buffer_t ;
struct TYPE_5__ {int length; int /*<<< orphan*/  value; } ;
struct TYPE_4__ {scalar_t__* enctypes; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 scalar_t__ GSS_C_NO_CREDENTIAL ; 
 scalar_t__ GSS_S_COMPLETE ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  free (scalar_t__*) ; 
 scalar_t__ krb5_ret_uint32 (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_mem (int /*<<< orphan*/ ,int) ; 
 scalar_t__* malloc (size_t) ; 

__attribute__((used)) static OM_uint32
allowed_enctypes(OM_uint32 *minor_status,
		 krb5_context context,
		 gss_cred_id_t *cred_handle,
		 const gss_buffer_t value)
{
    OM_uint32 major_stat;
    krb5_error_code ret;
    size_t len, i;
    krb5_enctype *enctypes = NULL;
    krb5_storage *sp = NULL;
    gsskrb5_cred cred;

    if (cred_handle == NULL || *cred_handle == GSS_C_NO_CREDENTIAL) {
	*minor_status = 0;
	return GSS_S_FAILURE;
    }

    cred = (gsskrb5_cred)*cred_handle;

    if ((value->length % 4) != 0) {
	*minor_status = 0;
	major_stat = GSS_S_FAILURE;
	goto out;
    }

    len = value->length / 4;
    enctypes = malloc((len + 1) * 4);
    if (enctypes == NULL) {
	*minor_status = ENOMEM;
	major_stat = GSS_S_FAILURE;
	goto out;
    }

    sp = krb5_storage_from_mem(value->value, value->length);
    if (sp == NULL) {
	*minor_status = ENOMEM;
	major_stat = GSS_S_FAILURE;
	goto out;
    }

    for (i = 0; i < len; i++) {
	uint32_t e;

	ret = krb5_ret_uint32(sp, &e);
	if (ret) {
	    *minor_status = ret;
	    major_stat =  GSS_S_FAILURE;
	    goto out;
	}
	enctypes[i] = e;
    }
    enctypes[i] = 0;

    if (cred->enctypes)
	free(cred->enctypes);
    cred->enctypes = enctypes;

    krb5_storage_free(sp);

    return GSS_S_COMPLETE;

out:
    if (sp)
	krb5_storage_free(sp);
    if (enctypes)
	free(enctypes);

    return major_stat;
}