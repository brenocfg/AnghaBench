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
struct truncate_options {int /*<<< orphan*/  realm_string; int /*<<< orphan*/  config_file_string; } ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  kadm5_server_context ;

/* Variables and functions */
 int /*<<< orphan*/  context ; 
 int /*<<< orphan*/ * get_kadmin_context (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kadm5_log_truncate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_err (int /*<<< orphan*/ ,int,scalar_t__,char*) ; 

int
iprop_truncate(struct truncate_options *opt, int argc, char **argv)
{
    kadm5_server_context *server_context;
    krb5_error_code ret;

    server_context = get_kadmin_context(opt->config_file_string,
					opt->realm_string);

    ret = kadm5_log_truncate (server_context);
    if (ret)
	krb5_err (context, 1, ret, "kadm5_log_truncate");

    return 0;
}