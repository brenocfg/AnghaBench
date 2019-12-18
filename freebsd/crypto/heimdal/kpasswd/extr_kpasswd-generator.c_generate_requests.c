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
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_get_init_creds_opt ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_data ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ KRB5KRB_AP_ERR_BAD_INTEGRITY ; 
 scalar_t__ KRB5KRB_AP_ERR_MODIFIED ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_set_forwardable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_set_proxiable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_set_tkt_life (int /*<<< orphan*/ *,int) ; 
 scalar_t__ krb5_get_init_creds_password (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_set_password (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nop_prompter ; 
 unsigned int rand () ; 
 unsigned int read_words (char const*,char***) ; 

__attribute__((used)) static void
generate_requests (const char *filename, unsigned nreq)
{
    krb5_context context;
    krb5_error_code ret;
    int i;
    char **words;
    unsigned nwords;

    ret = krb5_init_context (&context);
    if (ret)
	errx (1, "krb5_init_context failed: %d", ret);

    nwords = read_words (filename, &words);

    for (i = 0; i < nreq; ++i) {
	char *name = words[rand() % nwords];
	krb5_get_init_creds_opt *opt;
	krb5_creds cred;
	krb5_principal principal;
	int result_code;
	krb5_data result_code_string, result_string;
	char *old_pwd, *new_pwd;

	krb5_get_init_creds_opt_alloc (context, &opt);
	krb5_get_init_creds_opt_set_tkt_life (opt, 300);
	krb5_get_init_creds_opt_set_forwardable (opt, FALSE);
	krb5_get_init_creds_opt_set_proxiable (opt, FALSE);

	ret = krb5_parse_name (context, name, &principal);
	if (ret)
	    krb5_err (context, 1, ret, "krb5_parse_name %s", name);

	asprintf (&old_pwd, "%s", name);
	asprintf (&new_pwd, "%s2", name);

	ret = krb5_get_init_creds_password (context,
					    &cred,
					    principal,
					    old_pwd,
					    nop_prompter,
					    NULL,
					    0,
					    "kadmin/changepw",
					    opt);
	if( ret == KRB5KRB_AP_ERR_BAD_INTEGRITY
	    || ret == KRB5KRB_AP_ERR_MODIFIED) {
	    char *tmp;

	    tmp = new_pwd;
	    new_pwd = old_pwd;
	    old_pwd = tmp;

	    ret = krb5_get_init_creds_password (context,
						&cred,
						principal,
						old_pwd,
						nop_prompter,
						NULL,
						0,
						"kadmin/changepw",
						opt);
	}
	if (ret)
	    krb5_err (context, 1, ret, "krb5_get_init_creds_password");

	krb5_free_principal (context, principal);


	ret = krb5_set_password (context,
				 &cred,
				 new_pwd,
				 NULL,
				 &result_code,
				 &result_code_string,
				 &result_string);
	if (ret)
	    krb5_err (context, 1, ret, "krb5_change_password");

	free (old_pwd);
	free (new_pwd);
	krb5_free_cred_contents (context, &cred);
	krb5_get_init_creds_opt_free(context, opt);
    }
}