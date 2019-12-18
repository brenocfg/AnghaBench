#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rate ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {scalar_t__ n_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  SIGALRM ; 
 long default_rate ; 
 int /*<<< orphan*/  kmem ; 
 long lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,long,long) ; 
 TYPE_1__* nl ; 
 int /*<<< orphan*/  printf (char*,long,long) ; 
 long sigblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigmask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsetmask (long) ; 
 int sysdebug ; 
 long tick_rate ; 
 int verbose ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
SetClockRate(
	long rate
	)
{
	long mask;

	if (lseek(kmem, (off_t)nl[0].n_value, 0) == -1L)
	    return (-1);

	mask = sigblock(sigmask(SIGALRM));

	if (write(kmem, (caddr_t)&rate, sizeof(rate)) != sizeof(rate)) {
		sigsetmask(mask);
		return (-1);
	}

	sigsetmask(mask);

	if (rate != default_rate) {
		if (verbose > 3) {
			printf("adjtimed: clock rate (%lu) %ldus/s\n", rate,
			       (rate - default_rate) * tick_rate);
		}
		if (sysdebug > 3) {
			msyslog(LOG_INFO, "clock rate (%lu) %ldus/s", rate,
				(rate - default_rate) * tick_rate);
		}
	}

	return (0);
}