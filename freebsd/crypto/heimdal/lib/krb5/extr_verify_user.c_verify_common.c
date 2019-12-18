#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_verify_init_creds_opt ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/ * krb5_ccache ;
typedef  int /*<<< orphan*/  krb5_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_NT_SRV_HST ; 
 int /*<<< orphan*/  krb5_cc_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_default (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ krb5_cc_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_store_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_sname_to_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_verify_init_creds (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_verify_init_creds_opt_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_verify_init_creds_opt_set_ap_req_nofail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static krb5_error_code
verify_common (krb5_context context,
	       krb5_principal principal,
	       krb5_ccache ccache,
	       krb5_keytab keytab,
	       krb5_boolean secure,
	       const char *service,
	       krb5_creds cred)
{
    krb5_error_code ret;
    krb5_principal server;
    krb5_verify_init_creds_opt vopt;
    krb5_ccache id;

    ret = krb5_sname_to_principal (context, NULL, service, KRB5_NT_SRV_HST,
				   &server);
    if(ret)
	return ret;

    krb5_verify_init_creds_opt_init(&vopt);
    krb5_verify_init_creds_opt_set_ap_req_nofail(&vopt, secure);

    ret = krb5_verify_init_creds(context,
				 &cred,
				 server,
				 keytab,
				 NULL,
				 &vopt);
    krb5_free_principal(context, server);
    if(ret)
	return ret;
    if(ccache == NULL)
	ret = krb5_cc_default (context, &id);
    else
	id = ccache;
    if(ret == 0){
	ret = krb5_cc_initialize(context, id, principal);
	if(ret == 0){
	    ret = krb5_cc_store_cred(context, id, &cred);
	}
	if(ccache == NULL)
	    krb5_cc_close(context, id);
    }
    krb5_free_cred_contents(context, &cred);
    return ret;
}