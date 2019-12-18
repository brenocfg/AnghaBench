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
typedef  int /*<<< orphan*/  sigfunc ;

/* Variables and functions */
 int DEFAULTINCR ; 
 int RATE_ALL ; 
 int RATE_GET ; 
 int RATE_PUT ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,int) ; 
 char* onoff (int) ; 
 int rate_get ; 
 int rate_get_incr ; 
 int rate_put ; 
 int rate_put_incr ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int strsuftoi (char*) ; 
 int /*<<< orphan*/  ttyout ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  xsignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
parserate(int argc, char *argv[], int cmdlineopt)
{
	int dir, max, incr, showonly;
	sigfunc oldusr1, oldusr2;

	if (argc > 4 || (argc < (cmdlineopt ? 3 : 2))) {
 usage:
		if (cmdlineopt)
			UPRINTF(
	"usage: %s (all|get|put),maximum-bytes[,increment-bytes]]\n",
			    argv[0]);
		else
			UPRINTF(
	"usage: %s (all|get|put) [maximum-bytes [increment-bytes]]\n",
			    argv[0]);
		return -1;
	}
	dir = max = incr = showonly = 0;
#define	RATE_GET	1
#define	RATE_PUT	2
#define	RATE_ALL	(RATE_GET | RATE_PUT)

	if (strcasecmp(argv[1], "all") == 0)
		dir = RATE_ALL;
	else if (strcasecmp(argv[1], "get") == 0)
		dir = RATE_GET;
	else if (strcasecmp(argv[1], "put") == 0)
		dir = RATE_PUT;
	else
		goto usage;

	if (argc >= 3) {
		if ((max = strsuftoi(argv[2])) < 0)
			goto usage;
	} else
		showonly = 1;

	if (argc == 4) {
		if ((incr = strsuftoi(argv[3])) <= 0)
			goto usage;
	} else
		incr = DEFAULTINCR;

	oldusr1 = xsignal(SIGUSR1, SIG_IGN);
	oldusr2 = xsignal(SIGUSR2, SIG_IGN);
	if (dir & RATE_GET) {
		if (!showonly) {
			rate_get = max;
			rate_get_incr = incr;
		}
		if (!cmdlineopt || verbose)
			fprintf(ttyout,
		"Get transfer rate throttle: %s; maximum: %d; increment %d.\n",
			    onoff(rate_get), rate_get, rate_get_incr);
	}
	if (dir & RATE_PUT) {
		if (!showonly) {
			rate_put = max;
			rate_put_incr = incr;
		}
		if (!cmdlineopt || verbose)
			fprintf(ttyout,
		"Put transfer rate throttle: %s; maximum: %d; increment %d.\n",
			    onoff(rate_put), rate_put, rate_put_incr);
	}
	(void)xsignal(SIGUSR1, oldusr1);
	(void)xsignal(SIGUSR2, oldusr2);
	return 0;
}