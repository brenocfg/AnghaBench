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
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  open_logfile (char*) ; 
 int /*<<< orphan*/  sntp_init_logging (char*) ; 

void
testOpenLogfileTest(void)
{
	sntp_init_logging("TEST_PROGNAME2"); //this name is consistent through the entire program unless changed
	open_logfile("testLogfile.log");
	//open_logfile("/var/log/syslog"); //this gives me "Permission Denied" when i do %m

	msyslog(LOG_ERR, "Cannot open log file %s","abcXX");
	//cleanup_log(); //unnecessary  after log.c fix!

	return;
}