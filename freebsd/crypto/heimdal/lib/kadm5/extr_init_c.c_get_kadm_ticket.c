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
typedef  int /*<<< orphan*/  krb5_principal ;
typedef  scalar_t__ krb5_error_code ;
struct TYPE_6__ {int /*<<< orphan*/  server; int /*<<< orphan*/  client; } ;
typedef  TYPE_1__ krb5_creds ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  krb5_ccache ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 int /*<<< orphan*/  krb5_free_creds (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_free_principal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_get_credentials (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__**) ; 
 scalar_t__ krb5_parse_name (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static krb5_error_code
get_kadm_ticket(krb5_context context,
		krb5_ccache id,
		krb5_principal client,
		const char *server_name)
{
    krb5_error_code ret;
    krb5_creds in, *out;

    memset(&in, 0, sizeof(in));
    in.client = client;
    ret = krb5_parse_name(context, server_name, &in.server);
    if(ret)
	return ret;
    ret = krb5_get_credentials(context, 0, id, &in, &out);
    if(ret == 0)
	krb5_free_creds(context, out);
    krb5_free_principal(context, in.server);
    return ret;
}