#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_7__ {scalar_t__ endtime; scalar_t__ starttime; } ;
struct TYPE_8__ {TYPE_1__ times; int /*<<< orphan*/  server; int /*<<< orphan*/  client; } ;
typedef  TYPE_2__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  in_cred ;

/* Variables and functions */
 int /*<<< orphan*/  KRB5_GC_CACHED ; 
 scalar_t__ get_server (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ krb5_cc_get_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_free_creds (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_get_credentials (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__**) ; 
 int /*<<< orphan*/  krb5_warn (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static time_t
ticket_lifetime(krb5_context context, krb5_ccache cache,
		krb5_principal client, const char *server)
{
    krb5_creds in_cred, *cred;
    krb5_error_code ret;
    time_t timeout;

    memset(&in_cred, 0, sizeof(in_cred));

    ret = krb5_cc_get_principal(context, cache, &in_cred.client);
    if(ret) {
	krb5_warn(context, ret, "krb5_cc_get_principal");
	return 0;
    }
    ret = get_server(context, in_cred.client, server, &in_cred.server);
    if(ret) {
	krb5_free_principal(context, in_cred.client);
	krb5_warn(context, ret, "get_server");
	return 0;
    }

    ret = krb5_get_credentials(context, KRB5_GC_CACHED,
			       cache, &in_cred, &cred);
    krb5_free_principal(context, in_cred.client);
    krb5_free_principal(context, in_cred.server);
    if(ret) {
	krb5_warn(context, ret, "krb5_get_credentials");
	return 0;
    }
    timeout = cred->times.endtime - cred->times.starttime;
    if (timeout < 0)
	timeout = 0;
    krb5_free_creds(context, cred);
    return timeout;
}