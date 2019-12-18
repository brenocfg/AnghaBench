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
 int /*<<< orphan*/  abort_next ; 
 int /*<<< orphan*/  chat_logf (char*,...) ; 
 int /*<<< orphan*/  chat_send (char*) ; 
 int /*<<< orphan*/  clear_abort_next ; 
 int /*<<< orphan*/  clear_report_next ; 
 int /*<<< orphan*/  echo_next ; 
 int exit_code ; 
 char* expect_strtok (char*,char*) ; 
 scalar_t__ fail_reason ; 
 scalar_t__ get_string (char*) ; 
 int /*<<< orphan*/  hup_next ; 
 int /*<<< orphan*/  report_next ; 
 int /*<<< orphan*/  say_next ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  terminate (int) ; 
 int /*<<< orphan*/  timeout_next ; 

void
chat_expect(char *s)
{
    char *expect;
    char *reply;

    if (strcmp(s, "HANGUP") == 0) {
	++hup_next;
        return;
    }
 
    if (strcmp(s, "ABORT") == 0) {
	++abort_next;
	return;
    }

    if (strcmp(s, "CLR_ABORT") == 0) {
	++clear_abort_next;
	return;
    }

    if (strcmp(s, "REPORT") == 0) {
	++report_next;
	return;
    }

    if (strcmp(s, "CLR_REPORT") == 0) {
	++clear_report_next;
	return;
    }

    if (strcmp(s, "TIMEOUT") == 0) {
	++timeout_next;
	return;
    }

    if (strcmp(s, "ECHO") == 0) {
	++echo_next;
	return;
    }

    if (strcmp(s, "SAY") == 0) {
	++say_next;
	return;
    }

/*
 * Fetch the expect and reply string.
 */
    for (;;) {
	expect = expect_strtok (s, "-");
	s      = (char *) 0;

	if (expect == (char *) 0)
	    return;

	reply = expect_strtok (s, "-");

/*
 * Handle the expect string. If successful then exit.
 */
	if (get_string (expect))
	    return;

/*
 * If there is a sub-reply string then send it. Otherwise any condition
 * is terminal.
 */
	if (reply == (char *) 0 || exit_code != 3)
	    break;

	chat_send (reply);
    }

/*
 * The expectation did not occur. This is terminal.
 */
    if (fail_reason)
	chat_logf("Failed (%s)", fail_reason);
    else
	chat_logf("Failed");
    terminate(exit_code);
}