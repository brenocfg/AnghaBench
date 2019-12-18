#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  int /*<<< orphan*/  krb5_kdc_flags ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_8__ {int /*<<< orphan*/  server; int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/ * krb5_const_realm ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  Ticket ;

/* Variables and functions */
 scalar_t__ KRB5KDC_ERR_S_PRINCIPAL_UNKNOWN ; 
 scalar_t__ get_cred_kdc_capath_worker (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__**,TYPE_1__***) ; 
 int /*<<< orphan*/ * krb5_config_get_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * krb5_principal_get_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static krb5_error_code
get_cred_kdc_capath(krb5_context context,
		    krb5_kdc_flags flags,
		    krb5_ccache ccache,
		    krb5_creds *in_creds,
		    krb5_principal impersonate_principal,
		    Ticket *second_ticket,
		    krb5_creds **out_creds,
		    krb5_creds ***ret_tgts)
{
    krb5_error_code ret;
    krb5_const_realm client_realm, server_realm, try_realm;

    client_realm = krb5_principal_get_realm(context, in_creds->client);
    server_realm = krb5_principal_get_realm(context, in_creds->server);

    try_realm = client_realm;
    ret = get_cred_kdc_capath_worker(context, flags, ccache, in_creds, try_realm,
                                     impersonate_principal, second_ticket, out_creds,
                                     ret_tgts);

    if (ret == KRB5KDC_ERR_S_PRINCIPAL_UNKNOWN) {
        try_realm = krb5_config_get_string(context, NULL, "capaths",
                                           client_realm, server_realm, NULL);

        if (try_realm != NULL && strcmp(try_realm, client_realm)) {
            ret = get_cred_kdc_capath_worker(context, flags, ccache, in_creds,
                                             try_realm, impersonate_principal,
                                             second_ticket, out_creds, ret_tgts);
        }
    }

    return ret;
}