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
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  check_set_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 

int
main(int argc, char **argv)
{
    krb5_context context;
    krb5_error_code ret;

    ret = krb5_init_context(&context);
    if (ret)
	errx(1, "krb5_init_context %d", ret);

    check_set_time(context);
    check_set_time(context);
    check_set_time(context);
    check_set_time(context);
    check_set_time(context);

    krb5_free_context(context);

    return 0;
}