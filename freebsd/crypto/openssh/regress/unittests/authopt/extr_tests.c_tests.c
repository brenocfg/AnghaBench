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
typedef  int /*<<< orphan*/  LogLevel ;

/* Variables and functions */
 int /*<<< orphan*/  SYSLOG_FACILITY_USER ; 
 int /*<<< orphan*/  SYSLOG_LEVEL_DEBUG3 ; 
 int /*<<< orphan*/  SYSLOG_LEVEL_QUIET ; 
 int /*<<< orphan*/  log_init (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_authkeys_parse () ; 
 int /*<<< orphan*/  test_cert_parse () ; 
 scalar_t__ test_is_verbose () ; 
 int /*<<< orphan*/  test_merge () ; 

void
tests(void)
{
	extern char *__progname;
	LogLevel ll = test_is_verbose() ?
	    SYSLOG_LEVEL_DEBUG3 : SYSLOG_LEVEL_QUIET;

	/* test_cert_parse() are a bit spammy to error() by default... */
	log_init(__progname, ll, SYSLOG_FACILITY_USER, 1);

	test_authkeys_parse();
	test_cert_parse();
	test_merge();
}