#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/ * krb5_principal ;
typedef  int /*<<< orphan*/ * krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/ * krb5_ccache ;
typedef  scalar_t__ gss_cred_id_t ;
typedef  TYPE_1__* gss_buffer_t ;
struct TYPE_3__ {int /*<<< orphan*/  length; int /*<<< orphan*/  value; } ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ GSS_C_NO_CREDENTIAL ; 
 scalar_t__ GSS_S_FAILURE ; 
 scalar_t__ _gsskrb5_krb5_import_cred (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_resolve (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_resolve (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_ret_string (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_storage_from_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static OM_uint32
import_cred(OM_uint32 *minor_status,
	    krb5_context context,
            gss_cred_id_t *cred_handle,
            const gss_buffer_t value)
{
    OM_uint32 major_stat;
    krb5_error_code ret;
    krb5_principal keytab_principal = NULL;
    krb5_keytab keytab = NULL;
    krb5_storage *sp = NULL;
    krb5_ccache id = NULL;
    char *str;

    if (cred_handle == NULL || *cred_handle != GSS_C_NO_CREDENTIAL) {
	*minor_status = 0;
	return GSS_S_FAILURE;
    }

    sp = krb5_storage_from_mem(value->value, value->length);
    if (sp == NULL) {
	*minor_status = 0;
	return GSS_S_FAILURE;
    }

    /* credential cache name */
    ret = krb5_ret_string(sp, &str);
    if (ret) {
	*minor_status = ret;
	major_stat =  GSS_S_FAILURE;
	goto out;
    }
    if (str[0]) {
	ret = krb5_cc_resolve(context, str, &id);
	if (ret) {
	    *minor_status = ret;
	    major_stat =  GSS_S_FAILURE;
	    goto out;
	}
    }
    free(str);
    str = NULL;

    /* keytab principal name */
    ret = krb5_ret_string(sp, &str);
    if (ret == 0 && str[0])
	ret = krb5_parse_name(context, str, &keytab_principal);
    if (ret) {
	*minor_status = ret;
	major_stat = GSS_S_FAILURE;
	goto out;
    }
    free(str);
    str = NULL;

    /* keytab principal */
    ret = krb5_ret_string(sp, &str);
    if (ret) {
	*minor_status = ret;
	major_stat =  GSS_S_FAILURE;
	goto out;
    }
    if (str[0]) {
	ret = krb5_kt_resolve(context, str, &keytab);
	if (ret) {
	    *minor_status = ret;
	    major_stat =  GSS_S_FAILURE;
	    goto out;
	}
    }
    free(str);
    str = NULL;

    major_stat = _gsskrb5_krb5_import_cred(minor_status, id, keytab_principal,
					   keytab, cred_handle);
out:
    if (id)
	krb5_cc_close(context, id);
    if (keytab_principal)
	krb5_free_principal(context, keytab_principal);
    if (keytab)
	krb5_kt_close(context, keytab);
    if (str)
	free(str);
    if (sp)
	krb5_storage_free(sp);

    return major_stat;
}