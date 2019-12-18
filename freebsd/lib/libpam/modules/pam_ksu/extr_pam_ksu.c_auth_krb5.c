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
typedef  int /*<<< orphan*/  pam_handle_t ;
typedef  int /*<<< orphan*/  krb5_verify_init_creds_opt ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_get_init_creds_opt ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  PAM_AUTHTOK ; 
 int PAM_AUTH_ERR ; 
 int PAM_BUF_ERR ; 
 int /*<<< orphan*/  PAM_LOG (char*,char const*) ; 
 int PAM_SUCCESS ; 
 int /*<<< orphan*/  asprintf (char**,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_error_message (int /*<<< orphan*/ ,char const*) ; 
 char* krb5_get_error_message (int /*<<< orphan*/ ,long) ; 
 long krb5_get_init_creds_opt_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 long krb5_get_init_creds_password (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 long krb5_verify_init_creds (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_verify_init_creds_opt_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_verify_init_creds_opt_set_ap_req_nofail (int /*<<< orphan*/ *,int) ; 
 int pam_get_authtok (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,char*) ; 

__attribute__((used)) static int
auth_krb5(pam_handle_t *pamh, krb5_context context, const char *su_principal_name,
    krb5_principal su_principal)
{
	krb5_creds	 creds;
	krb5_get_init_creds_opt *gic_opt;
	krb5_verify_init_creds_opt vic_opt;
	const char	*pass;
	char		*prompt;
	long		 rv;
	int		 pamret;

	prompt = NULL;
	krb5_verify_init_creds_opt_init(&vic_opt);
	if (su_principal_name != NULL)
		(void)asprintf(&prompt, "Password for %s:", su_principal_name);
	else
		(void)asprintf(&prompt, "Password:");
	if (prompt == NULL)
		return (PAM_BUF_ERR);
	pass = NULL;
	pamret = pam_get_authtok(pamh, PAM_AUTHTOK, &pass, prompt);
	free(prompt);
	if (pamret != PAM_SUCCESS)
		return (pamret);
	rv = krb5_get_init_creds_opt_alloc(context, &gic_opt);
	if (rv != 0) {
		const char *msg = krb5_get_error_message(context, rv);
		PAM_LOG("krb5_get_init_creds_opt_alloc: %s", msg);
		krb5_free_error_message(context, msg);
		return (PAM_AUTH_ERR);
	}
	rv = krb5_get_init_creds_password(context, &creds, su_principal,
	    pass, NULL, NULL, 0, NULL, gic_opt);
	krb5_get_init_creds_opt_free(context, gic_opt);
	if (rv != 0) {
		const char *msg = krb5_get_error_message(context, rv);
		PAM_LOG("krb5_get_init_creds_password: %s", msg);
		krb5_free_error_message(context, msg);
		return (PAM_AUTH_ERR);
	}
	krb5_verify_init_creds_opt_set_ap_req_nofail(&vic_opt, 1);
	rv = krb5_verify_init_creds(context, &creds, NULL, NULL, NULL,
	    &vic_opt);
	krb5_free_cred_contents(context, &creds);
	if (rv != 0) {
		const char *msg = krb5_get_error_message(context, rv);
		PAM_LOG("krb5_verify_init_creds: %s", msg);
		krb5_free_error_message(context, msg);
		return (PAM_AUTH_ERR);
	}
	return (PAM_SUCCESS);
}