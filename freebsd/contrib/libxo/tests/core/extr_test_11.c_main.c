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

/* Variables and functions */
 int LOG_DAEMON ; 
 int LOG_INFO ; 
 int LOG_KERN ; 
 int LOG_LOCAL4 ; 
 int LOG_MAIL ; 
 int LOG_NOTICE ; 
 int /*<<< orphan*/  LOG_PERROR ; 
 int /*<<< orphan*/  setenv (char*,char const*,int) ; 
 int /*<<< orphan*/  test_syslog_close ; 
 int /*<<< orphan*/  test_syslog_open ; 
 int /*<<< orphan*/  test_syslog_send ; 
 int /*<<< orphan*/  tzset () ; 
 int /*<<< orphan*/  xo_close_container_h (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xo_finish () ; 
 int /*<<< orphan*/  xo_open_container_h (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xo_open_log (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xo_parse_args (int,char**) ; 
 int /*<<< orphan*/  xo_set_syslog_enterprise_id (int) ; 
 int /*<<< orphan*/  xo_set_syslog_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_set_unit_test_mode (int) ; 
 int /*<<< orphan*/  xo_set_version (char*) ; 
 scalar_t__ xo_streq (char*,char*) ; 
 int /*<<< orphan*/  xo_syslog (int,char*,char*,...) ; 

int
main (int argc, char **argv)
{
    int unit_test = 1;
    int fire = 0;
    const char *tzone = "EST";

    argc = xo_parse_args(argc, argv);
    if (argc < 0)
	return 1;

    for (argc = 1; argv[argc]; argc++) {
	if (xo_streq(argv[argc], "full"))
	    unit_test = 0;
	else if (xo_streq(argv[argc], "fire"))
	    fire = 1;
	else if (xo_streq(argv[argc], "tz"))
	    tzone = argv[++argc];
    }

    setenv("TZ", tzone, 1);
    tzset();

    if (!fire) {
	xo_set_syslog_handler(test_syslog_open, test_syslog_send,
			      test_syslog_close);
    }

    if (unit_test) {
	xo_set_unit_test_mode(1);
	xo_open_log("test-program", LOG_PERROR, 0);
    }

    xo_set_version("3.1.4");
    xo_set_syslog_enterprise_id(42); /* SunOs */

    xo_open_container_h(NULL, "top");

    xo_syslog(LOG_INFO | LOG_KERN, "animal-status",
	      "The {:animal} is {:state}", "snake", "loose");
    xo_syslog(LOG_INFO | LOG_MAIL, "animal-consumed",
	      "My {:animal} ate your {:pet}", "snake", "hamster");
    xo_syslog(LOG_NOTICE | LOG_DAEMON, "animal-talk",
	      "{:count/%d} {:animal} said {:quote}", 1, "owl", "\"e=m\\c[2]\"");

    /*
      <165>1 2003-10-11T22:14:15.003Z mymachine.example.com
           evntslog - ID47 [exampleSDID@32473 iut="3" eventSource=
           "Application" eventID="1011"] BOMAn application
           event log entry...

   This example is modeled after Example 1.  However, this time it
   contains STRUCTURED-DATA, a single element with the value
   "[exampleSDID@32473 iut="3" eventSource="Application"
   eventID="1011"]".  The MSG itself is "An application event log
   entry..."  The BOM at the beginning of MSG indicates UTF-8 encoding.
    */

    xo_set_syslog_enterprise_id(32473);
    xo_syslog(LOG_LOCAL4 | LOG_NOTICE, "ID47",
	      "{e:iut/%u}An {:event-source} {:event-id/%u} log entry",
	      3, "application", 1011);

    xo_close_container_h(NULL, "top");

    xo_finish();

    return 0;
}