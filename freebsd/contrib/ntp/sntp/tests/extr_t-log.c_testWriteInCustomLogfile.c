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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  TEST_ASSERT_TRUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  open_logfile (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  remove (char*) ; 
 int /*<<< orphan*/  sntp_init_logging (char*) ; 
 char* strstr (char*,char*) ; 

void
testWriteInCustomLogfile(void)
{
	char testString[256] = "12345 ABC";
	char testName[256] = "TEST_PROGNAME3";

	(void)remove("testLogfile2.log");

	sntp_init_logging(testName);
	open_logfile("testLogfile2.log"); // ./ causing issues
	//sntp_init_logging(testName);


	msyslog(LOG_ERR, "%s", testString);
	FILE * f = fopen("testLogfile2.log","r");
	char line[256];

	TEST_ASSERT_TRUE( f != NULL);

	//should be only 1 line
	while (fgets(line, sizeof(line), f)) {
		printf("%s", line);
	}


	char* x = strstr(line,testName);

	TEST_ASSERT_TRUE( x != NULL);

	x = strstr(line,testString);
	TEST_ASSERT_TRUE( x != NULL);
	//cleanup_log();
	fclose(f); //using this will also cause segfault, because at the end, log.c will  call (using atexit(func) function) cleanup_log(void)-> fclose(syslog_file);
	//After the 1st fclose, syslog_file = NULL, and is never reset -> hopefully fixed by editing log.c
	//TEST_ASSERT_EQUAL_STRING(testString,line); //doesn't work, line is dynamic because the process name is random.

	return;
}