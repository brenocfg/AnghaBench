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
struct krb5_krbhst_info {int dummy; } ;
struct krb5_krbhst_data {int dummy; } ;
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  append_host_hostinfo (struct krb5_krbhst_data*,struct krb5_krbhst_info*) ; 
 struct krb5_krbhst_info* parse_hostspec (int /*<<< orphan*/ ,struct krb5_krbhst_data*,char const*,int,int) ; 

__attribute__((used)) static krb5_error_code
append_host_string(krb5_context context, struct krb5_krbhst_data *kd,
		   const char *host, int def_port, int port)
{
    struct krb5_krbhst_info *hi;

    hi = parse_hostspec(context, kd, host, def_port, port);
    if(hi == NULL)
	return ENOMEM;

    append_host_hostinfo(kd, hi);
    return 0;
}