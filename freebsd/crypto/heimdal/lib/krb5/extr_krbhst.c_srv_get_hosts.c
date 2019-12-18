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
struct krb5_krbhst_data {int /*<<< orphan*/  realm; int /*<<< orphan*/  port; } ;
typedef  int /*<<< orphan*/  krb5_krbhst_info ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  _krb5_debug (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,char const*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  append_host_hostinfo (struct krb5_krbhst_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 scalar_t__ srv_find_realm (int /*<<< orphan*/ ,int /*<<< orphan*/ ***,int*,int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
srv_get_hosts(krb5_context context, struct krb5_krbhst_data *kd,
	      const char *proto, const char *service)
{
    krb5_error_code ret;
    krb5_krbhst_info **res;
    int count, i;

    ret = srv_find_realm(context, &res, &count, kd->realm, "SRV", proto, service,
			 kd->port);
    _krb5_debug(context, 2, "searching DNS for realm %s %s.%s -> %d",
		kd->realm, proto, service, ret);
    if (ret)
	return;
    for(i = 0; i < count; i++)
	append_host_hostinfo(kd, res[i]);
    free(res);
}