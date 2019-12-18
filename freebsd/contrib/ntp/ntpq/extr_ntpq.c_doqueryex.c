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
typedef  int /*<<< orphan*/  u_short ;
typedef  int /*<<< orphan*/  associd_t ;

/* Variables and functions */
 int ERR_INCOMPLETE ; 
 int ERR_TIMEOUT ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int getresponse (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t*,char const**,int) ; 
 int /*<<< orphan*/  havehost ; 
 int sendrequest (int,int /*<<< orphan*/ ,int,size_t,char const*) ; 
 int /*<<< orphan*/  sequence ; 
 int /*<<< orphan*/  show_error_msg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int
doqueryex(
	int opcode,
	associd_t associd,
	int auth,
	size_t qsize,
	const char *qdata,
	u_short *rstatus,
	size_t *rsize,
	const char **rdata,
	int quiet
	)
{
	int res;
	int done;

	/*
	 * Check to make sure host is open
	 */
	if (!havehost) {
		fprintf(stderr, "***No host open, use `host' command\n");
		return -1;
	}

	done = 0;
	sequence++;

    again:
	/*
	 * send a request
	 */
	res = sendrequest(opcode, associd, auth, qsize, qdata);
	if (res != 0)
		return res;

	/*
	 * Get the response.  If we got a standard error, print a message
	 */
	res = getresponse(opcode, associd, rstatus, rsize, rdata, done);

	if (res > 0) {
		if (!done && (res == ERR_TIMEOUT || res == ERR_INCOMPLETE)) {
			if (res == ERR_INCOMPLETE) {
				/*
				 * better bump the sequence so we don't
				 * get confused about differing fragments.
				 */
				sequence++;
			}
			done = 1;
			goto again;
		}
		if (!quiet)
			show_error_msg(res, associd);

	}
	return res;
}