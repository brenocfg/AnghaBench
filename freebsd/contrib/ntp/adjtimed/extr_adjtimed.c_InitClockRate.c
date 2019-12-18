#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ n_type; } ;

/* Variables and functions */
 int DEFAULT_RATE ; 
 int GetClockRate () ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int MILLION ; 
 int /*<<< orphan*/  O_RDWR ; 
 int TICK_ADJ ; 
 int UNKNOWN_RATE ; 
 int default_rate ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 int kmem ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* nl ; 
 int /*<<< orphan*/  nlist (char*,TYPE_1__*) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int slew_rate ; 
 int /*<<< orphan*/  stderr ; 
 int tick_rate ; 

int
InitClockRate(void)
{
	if ((kmem = open("/dev/kmem", O_RDWR)) == -1) {
		msyslog(LOG_ERR, "open(/dev/kmem): %m");
		perror("adjtimed: open(/dev/kmem)");
		return (-1);
	}

	nlist("/hp-ux", nl);

	if (nl[0].n_type == 0) {
		fputs("adjtimed: /hp-ux has no symbol table\n", stderr);
		msyslog(LOG_ERR, "/hp-ux has no symbol table");
		return (-1);
	}
	/*
	 * Set the default to the system's original value
	 */
	default_rate = GetClockRate();
	if (default_rate == UNKNOWN_RATE) default_rate = DEFAULT_RATE;
	tick_rate = (MILLION / default_rate);
	slew_rate = TICK_ADJ * tick_rate;
	fprintf(stderr,"default_rate=%ld, tick_rate=%ld, slew_rate=%ld\n",default_rate,tick_rate,slew_rate);

	return (0);
}