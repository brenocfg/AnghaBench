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
typedef  int /*<<< orphan*/  krb5_log_facility ;
typedef  scalar_t__ krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  krb5_addlog_dest (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  krb5_free_context (int /*<<< orphan*/ ) ; 
 scalar_t__ krb5_init_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  krb5_initlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  krb5_set_warn_dest (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
check_log(void)
{
    int i;

    for (i = 0; i < 10; i++) {
	krb5_log_facility *logfacility;
	krb5_context context;
	krb5_error_code ret;

	ret = krb5_init_context(&context);
	if (ret)
	    errx (1, "krb5_init_context failed: %d", ret);

	krb5_initlog(context, "test-mem", &logfacility);
	krb5_addlog_dest(context, logfacility, "0/STDERR:");
	krb5_set_warn_dest(context, logfacility);

	krb5_free_context(context);
    }
}