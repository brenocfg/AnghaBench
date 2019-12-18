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
typedef  scalar_t__ time_t ;
struct tm {int tm_isdst; int tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_wday; int /*<<< orphan*/  tm_mday; scalar_t__ tm_sec; } ;

/* Variables and functions */
 int EOF ; 
#define  MIDNIGHT 134 
#define  MINUS 133 
#define  NOON 132 
#define  NOW 131 
#define  NUMBER 130 
#define  PLUS 129 
#define  TEATIME 128 
 int /*<<< orphan*/  expect (int) ; 
 int /*<<< orphan*/  init_scanner (int,char**) ; 
 struct tm* localtime (scalar_t__*) ; 
 int /*<<< orphan*/  minus (struct tm*) ; 
 scalar_t__ mktime (struct tm*) ; 
 int /*<<< orphan*/  month (struct tm*) ; 
 int optind ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  plus (struct tm*) ; 
 int scc ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tod (struct tm*) ; 
 int token () ; 
 int /*<<< orphan*/  usage () ; 

time_t
parsetime(int argc, char **argv)
{
/* Do the argument parsing, die if necessary, and return the time the job
 * should be run.
 */
    time_t nowtimer, runtimer;
    struct tm nowtime, runtime;
    int hr = 0;
    /* this MUST be initialized to zero for midnight/noon/teatime */

    nowtimer = time(NULL);
    nowtime = *localtime(&nowtimer);

    runtime = nowtime;
    runtime.tm_sec = 0;
    runtime.tm_isdst = 0;

    if (argc <= optind)
	usage();

    init_scanner(argc-optind, argv+optind);

    switch (token()) {
    case NOW:	
	    if (scc < 1) {
		return nowtimer;
	    }
	    /* now is optional prefix for PLUS tree */
	    expect(PLUS);
	    /* FALLTHROUGH */
    case PLUS:
	    plus(&runtime);
	    break;

	    /* MINUS is different from PLUS in that NOW is not
	     * an optional prefix for it
	     */
    case MINUS:
	    minus(&runtime);
	    break;
    case NUMBER:
	    tod(&runtime);
	    month(&runtime);
	    break;

	    /* evil coding for TEATIME|NOON|MIDNIGHT - we've initialised
	     * hr to zero up above, then fall into this case in such a
	     * way so we add +12 +4 hours to it for teatime, +12 hours
	     * to it for noon, and nothing at all for midnight, then
	     * set our runtime to that hour before leaping into the
	     * month scanner
	     */
    case TEATIME:
	    hr += 4;
	    /* FALLTHROUGH */
    case NOON:
	    hr += 12;
	    /* FALLTHROUGH */
    case MIDNIGHT:
	    if (runtime.tm_hour >= hr) {
		runtime.tm_mday++;
		runtime.tm_wday++;
	    }
	    runtime.tm_hour = hr;
	    runtime.tm_min = 0;
	    token();
	    /* FALLTHROUGH to month setting */
    default:
	    month(&runtime);
	    break;
    } /* ugly case statement */
    expect(EOF);

    /* convert back to time_t
     */
    runtime.tm_isdst = -1;
    runtimer = mktime(&runtime);

    if (runtimer < 0)
	panic("garbled time");

    if (nowtimer > runtimer)
	panic("trying to travel back in time");

    return runtimer;
}