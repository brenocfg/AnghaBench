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
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ krb5_data ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  gss_cred_id_t ;
struct TYPE_7__ {int /*<<< orphan*/  length; int /*<<< orphan*/  value; } ;
typedef  TYPE_2__ gss_buffer_desc ;
typedef  scalar_t__ OM_uint32 ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  GSS_C_NO_CREDENTIAL ; 
 int /*<<< orphan*/  GSS_KRB5_IMPORT_CRED_X ; 
 scalar_t__ GSS_S_FAILURE ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ gss_set_cred_option (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ krb5_cc_get_full_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  krb5_data_free (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_get_full_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/ * krb5_storage_emem () ; 
 int /*<<< orphan*/  krb5_storage_free (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_storage_to_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ krb5_store_string (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 

OM_uint32
gss_krb5_import_cred(OM_uint32 *minor_status,
		     krb5_ccache id,
		     krb5_principal keytab_principal,
		     krb5_keytab keytab,
		     gss_cred_id_t *cred)
{
    gss_buffer_desc buffer;
    OM_uint32 major_status;
    krb5_context context;
    krb5_error_code ret;
    krb5_storage *sp;
    krb5_data data;
    char *str;

    *cred = GSS_C_NO_CREDENTIAL;

    ret = krb5_init_context(&context);
    if (ret) {
	*minor_status = ret;
	return GSS_S_FAILURE;
    }

    sp = krb5_storage_emem();
    if (sp == NULL) {
	*minor_status = ENOMEM;
	major_status = GSS_S_FAILURE;
	goto out;
    }

    if (id) {
	ret = krb5_cc_get_full_name(context, id, &str);
	if (ret == 0) {
	    ret = krb5_store_string(sp, str);
	    free(str);
	}
    } else
	ret = krb5_store_string(sp, "");
    if (ret) {
	*minor_status = ret;
	major_status = GSS_S_FAILURE;
	goto out;
    }

    if (keytab_principal) {
	ret = krb5_unparse_name(context, keytab_principal, &str);
	if (ret == 0) {
	    ret = krb5_store_string(sp, str);
	    free(str);
	}
    } else
	krb5_store_string(sp, "");
    if (ret) {
	*minor_status = ret;
	major_status = GSS_S_FAILURE;
	goto out;
    }


    if (keytab) {
	ret = krb5_kt_get_full_name(context, keytab, &str);
	if (ret == 0) {
	    ret = krb5_store_string(sp, str);
	    free(str);
	}
    } else
	krb5_store_string(sp, "");
    if (ret) {
	*minor_status = ret;
	major_status = GSS_S_FAILURE;
	goto out;
    }

    ret = krb5_storage_to_data(sp, &data);
    if (ret) {
	*minor_status = ret;
	major_status = GSS_S_FAILURE;
	goto out;
    }

    buffer.value = data.data;
    buffer.length = data.length;
    
    major_status = gss_set_cred_option(minor_status,
				       cred,
				       GSS_KRB5_IMPORT_CRED_X,
				       &buffer);
    krb5_data_free(&data);
out:
    if (sp)
	krb5_storage_free(sp);
    krb5_free_context(context);
    return major_status;
}