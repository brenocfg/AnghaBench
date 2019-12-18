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
struct peer {int delay; int rootdelay; int disp; int update; int rootdisp; int jitter; } ;

/* Variables and functions */
 int clock_phi ; 
 int current_time ; 
 double sys_mindisp ; 

__attribute__((used)) static double
root_distance(
	struct peer *peer	/* peer structure pointer */
	)
{
	double	dtemp;

	/*
	 * Root Distance (LAMBDA) is defined as:
	 * (delta + DELTA)/2 + epsilon + EPSILON + D
	 *
	 * where:
	 *  delta   is the round-trip delay
	 *  DELTA   is the root delay
	 *  epsilon is the peer dispersion
	 *	    + (15 usec each second)
	 *  EPSILON is the root dispersion
	 *  D       is sys_jitter
	 *
	 * NB: Think hard about why we are using these values, and what
	 * the alternatives are, and the various pros/cons.
	 *
	 * DLM thinks these are probably the best choices from any of the
	 * other worse choices.
	 */
	dtemp = (peer->delay + peer->rootdelay) / 2
		+ peer->disp
		  + clock_phi * (current_time - peer->update)
		+ peer->rootdisp
		+ peer->jitter;
	/*
	 * Careful squeak here. The value returned must be greater than
	 * the minimum root dispersion in order to avoid clockhop with
	 * highly precise reference clocks. Note that the root distance
	 * cannot exceed the sys_maxdist, as this is the cutoff by the
	 * selection algorithm.
	 */
	if (dtemp < sys_mindisp)
		dtemp = sys_mindisp;
	return (dtemp);
}