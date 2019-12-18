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
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  cred ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*,char*) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_get_init_creds_password (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 unsigned int rand () ; 
 unsigned int read_words (char const*,char***) ; 

__attribute__((used)) static void
generate_requests (const char *filename, unsigned nreq)
{
    krb5_principal client;
    krb5_context context;
    krb5_error_code ret;
    krb5_creds cred;
    int i;
    char **words;
    unsigned nwords;

    ret = krb5_init_context (&context);
    if (ret)
	errx (1, "krb5_init_context failed: %d", ret);

    nwords = read_words (filename, &words);

    for (i = 0; i < nreq; ++i) {
	char *name = words[rand() % nwords];

	memset(&cred, 0, sizeof(cred));

	ret = krb5_parse_name (context, name, &client);
	if (ret)
	    krb5_err (context, 1, ret, "krb5_parse_name %s", name);

	ret = krb5_get_init_creds_password (context, &cred, client, "",
					    NULL, NULL, 0, NULL, NULL);
	if (ret)
	    krb5_free_cred_contents (context, &cred);
	krb5_free_principal(context, client);
    }
}