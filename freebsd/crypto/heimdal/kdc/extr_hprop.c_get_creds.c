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
typedef  int /*<<< orphan*/  krb5_preauthtype ;
typedef  int /*<<< orphan*/  krb5_keytab ;
typedef  int /*<<< orphan*/  krb5_get_init_creds_opt ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;

/* Variables and functions */
 int /*<<< orphan*/  HPROP_NAME ; 
 int /*<<< orphan*/  KRB5_PADATA_ENC_TIMESTAMP ; 
 int /*<<< orphan*/  hdb_kt_ops ; 
 scalar_t__ krb5_cc_initialize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_cc_new_unique (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_store_cred (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_cc_type_memory ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  krb5_free_cred_contents (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_get_init_creds_keytab (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_get_init_creds_opt_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_get_init_creds_opt_set_preauth_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ krb5_kt_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_kt_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_kt_resolve (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_make_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktname ; 

__attribute__((used)) static void
get_creds(krb5_context context, krb5_ccache *cache)
{
    krb5_keytab keytab;
    krb5_principal client;
    krb5_error_code ret;
    krb5_get_init_creds_opt *init_opts;
    krb5_preauthtype preauth = KRB5_PADATA_ENC_TIMESTAMP;
    krb5_creds creds;

    ret = krb5_kt_register(context, &hdb_kt_ops);
    if(ret) krb5_err(context, 1, ret, "krb5_kt_register");

    ret = krb5_kt_resolve(context, ktname, &keytab);
    if(ret) krb5_err(context, 1, ret, "krb5_kt_resolve");

    ret = krb5_make_principal(context, &client, NULL,
			      "kadmin", HPROP_NAME, NULL);
    if(ret) krb5_err(context, 1, ret, "krb5_make_principal");

    ret = krb5_get_init_creds_opt_alloc(context, &init_opts);
    if(ret) krb5_err(context, 1, ret, "krb5_get_init_creds_opt_alloc");
    krb5_get_init_creds_opt_set_preauth_list(init_opts, &preauth, 1);

    ret = krb5_get_init_creds_keytab(context, &creds, client, keytab, 0, NULL, init_opts);
    if(ret) krb5_err(context, 1, ret, "krb5_get_init_creds");

    krb5_get_init_creds_opt_free(context, init_opts);

    ret = krb5_kt_close(context, keytab);
    if(ret) krb5_err(context, 1, ret, "krb5_kt_close");

    ret = krb5_cc_new_unique(context, krb5_cc_type_memory, NULL, cache);
    if(ret) krb5_err(context, 1, ret, "krb5_cc_new_unique");

    ret = krb5_cc_initialize(context, *cache, client);
    if(ret) krb5_err(context, 1, ret, "krb5_cc_initialize");

    krb5_free_principal(context, client);

    ret = krb5_cc_store_cred(context, *cache, &creds);
    if(ret) krb5_err(context, 1, ret, "krb5_cc_store_cred");

    krb5_free_cred_contents(context, &creds);
}