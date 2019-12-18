#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_4__ {int /*<<< orphan*/  client; int /*<<< orphan*/  server; } ;
typedef  TYPE_1__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  scalar_t__ krb5_const_principal ;
typedef  int /*<<< orphan*/  krb5_ccache ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_CONF_NAME ; 
 int /*<<< orphan*/  KRB5_REALM_NAME ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_copy_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_make_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_unparse_name (int /*<<< orphan*/ ,scalar_t__,char**) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static krb5_error_code
build_conf_principals(krb5_context context, krb5_ccache id,
		      krb5_const_principal principal,
		      const char *name, krb5_creds *cred)
{
    krb5_principal client;
    krb5_error_code ret;
    char *pname = NULL;

    memset(cred, 0, sizeof(*cred));

    ret = krb5_cc_get_principal(context, id, &client);
    if (ret)
	return ret;

    if (principal) {
	ret = krb5_unparse_name(context, principal, &pname);
	if (ret)
	    return ret;
    }

    ret = krb5_make_principal(context, &cred->server,
			      KRB5_REALM_NAME,
			      KRB5_CONF_NAME, name, pname, NULL);
    free(pname);
    if (ret) {
	krb5_free_principal(context, client);
	return ret;
    }
    ret = krb5_copy_principal(context, client, &cred->client);
    krb5_free_principal(context, client);
    return ret;
}