#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * krb5_prompter_fct ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  int /*<<< orphan*/  krb5_get_init_creds_opt ;
typedef  int krb5_error_code ;
struct TYPE_6__ {int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int KADM5_BAD_PASSWORD ; 
#define  KRB5KRB_AP_ERR_BAD_INTEGRITY 130 
#define  KRB5KRB_AP_ERR_MODIFIED 129 
#define  KRB5_LIBOS_PWDINTR 128 
 int krb5_cc_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int krb5_cc_new_unique (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int krb5_cc_store_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_cc_type_memory ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int krb5_get_init_creds_keytab (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int krb5_get_init_creds_opt_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_set_default_flags (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_set_forwardable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_set_proxiable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int krb5_get_init_creds_password (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int krb5_kt_default (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int krb5_kt_resolve (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_principal_get_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
get_new_cache(krb5_context context,
	      krb5_principal client,
	      const char *password,
	      krb5_prompter_fct prompter,
	      const char *keytab,
	      const char *server_name,
	      krb5_ccache *ret_cache)
{
    krb5_error_code ret;
    krb5_creds cred;
    krb5_get_init_creds_opt *opt;
    krb5_ccache id;

    ret = krb5_get_init_creds_opt_alloc (context, &opt);
    if (ret)
	return ret;

    krb5_get_init_creds_opt_set_default_flags(context, "kadmin",
					      krb5_principal_get_realm(context,
								       client),
					      opt);


    krb5_get_init_creds_opt_set_forwardable (opt, FALSE);
    krb5_get_init_creds_opt_set_proxiable (opt, FALSE);

    if(password == NULL && prompter == NULL) {
	krb5_keytab kt;
	if(keytab == NULL)
	    ret = krb5_kt_default(context, &kt);
	else
	    ret = krb5_kt_resolve(context, keytab, &kt);
	if(ret) {
	    krb5_get_init_creds_opt_free(context, opt);
	    return ret;
	}
	ret = krb5_get_init_creds_keytab (context,
					  &cred,
					  client,
					  kt,
					  0,
					  server_name,
					  opt);
	krb5_kt_close(context, kt);
    } else {
	ret = krb5_get_init_creds_password (context,
					    &cred,
					    client,
					    password,
					    prompter,
					    NULL,
					    0,
					    server_name,
					    opt);
    }
    krb5_get_init_creds_opt_free(context, opt);
    switch(ret){
    case 0:
	break;
    case KRB5_LIBOS_PWDINTR:	/* don't print anything if it was just C-c:ed */
    case KRB5KRB_AP_ERR_BAD_INTEGRITY:
    case KRB5KRB_AP_ERR_MODIFIED:
	return KADM5_BAD_PASSWORD;
    default:
	return ret;
    }
    ret = krb5_cc_new_unique(context, krb5_cc_type_memory, NULL, &id);
    if(ret)
	return ret;
    ret = krb5_cc_initialize (context, id, cred.client);
    if (ret)
	return ret;
    ret = krb5_cc_store_cred (context, id, &cred);
    if (ret)
	return ret;
    krb5_free_cred_contents (context, &cred);
    *ret_cache = id;
    return 0;
}