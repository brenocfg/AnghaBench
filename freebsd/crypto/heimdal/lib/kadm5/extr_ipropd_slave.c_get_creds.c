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
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  int /*<<< orphan*/  krb5_get_init_creds_opt ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  keytab_buf ;

/* Variables and functions */
 int /*<<< orphan*/  IPROP_NAME ; 
 int /*<<< orphan*/  KRB5_NT_SRV_HST ; 
 int /*<<< orphan*/  asprintf (char**,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ krb5_cc_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_new_unique (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_store_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_cc_type_memory ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_get_init_creds_keytab (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_get_init_creds_opt_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_kt_default_name (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ krb5_kt_resolve (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_sname_to_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slave_str ; 

__attribute__((used)) static void
get_creds(krb5_context context, const char *keytab_str,
	  krb5_ccache *cache, const char *serverhost)
{
    krb5_keytab keytab;
    krb5_principal client;
    krb5_error_code ret;
    krb5_get_init_creds_opt *init_opts;
    krb5_creds creds;
    char *server;
    char keytab_buf[256];

    if (keytab_str == NULL) {
	ret = krb5_kt_default_name (context, keytab_buf, sizeof(keytab_buf));
	if (ret)
	    krb5_err (context, 1, ret, "krb5_kt_default_name");
	keytab_str = keytab_buf;
    }

    ret = krb5_kt_resolve(context, keytab_str, &keytab);
    if(ret)
	krb5_err(context, 1, ret, "%s", keytab_str);


    ret = krb5_sname_to_principal (context, slave_str, IPROP_NAME,
				   KRB5_NT_SRV_HST, &client);
    if (ret) krb5_err(context, 1, ret, "krb5_sname_to_principal");

    ret = krb5_get_init_creds_opt_alloc(context, &init_opts);
    if (ret) krb5_err(context, 1, ret, "krb5_get_init_creds_opt_alloc");

    asprintf (&server, "%s/%s", IPROP_NAME, serverhost);
    if (server == NULL)
	krb5_errx (context, 1, "malloc: no memory");

    ret = krb5_get_init_creds_keytab(context, &creds, client, keytab,
				     0, server, init_opts);
    free (server);
    krb5_get_init_creds_opt_free(context, init_opts);
    if(ret) krb5_err(context, 1, ret, "krb5_get_init_creds");

    ret = krb5_kt_close(context, keytab);
    if(ret) krb5_err(context, 1, ret, "krb5_kt_close");

    ret = krb5_cc_new_unique(context, krb5_cc_type_memory, NULL, cache);
    if(ret) krb5_err(context, 1, ret, "krb5_cc_new_unique");

    ret = krb5_cc_initialize(context, *cache, client);
    if(ret) krb5_err(context, 1, ret, "krb5_cc_initialize");

    ret = krb5_cc_store_cred(context, *cache, &creds);
    if(ret) krb5_err(context, 1, ret, "krb5_cc_store_cred");

    krb5_free_cred_contents(context, &creds);
    krb5_free_principal(context, client);
}