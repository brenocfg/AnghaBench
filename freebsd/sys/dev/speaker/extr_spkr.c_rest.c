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
 int PCATCH ; 
 int SPKRPRI ; 
 int /*<<< orphan*/  endrest ; 
 int hz ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  tsleep (int /*<<< orphan*/ *,int,char*,int) ; 

__attribute__((used)) static void
rest(int centisecs)
{
	int timo;

	/*
	 * Set timeout to endrest function, then give up the timeslice.
	 * This is so other processes can execute while the rest is being
	 * waited out.
	 */
#ifdef DEBUG
	(void) printf("rest: %d\n", centisecs);
#endif /* DEBUG */
	timo = centisecs * hz / 100;
	if (timo > 0)
		tsleep(&endrest, SPKRPRI | PCATCH, "spkrrs", timo);
}