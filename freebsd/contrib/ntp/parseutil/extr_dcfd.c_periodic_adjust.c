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
 scalar_t__ ADJINTERVAL ; 
 scalar_t__ PHASE_WEIGHT ; 
 long R_SHIFT (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ USECSCALE ; 
 int /*<<< orphan*/  accum_drift ; 
 int /*<<< orphan*/  adj_time (long) ; 
 int /*<<< orphan*/  adjustments ; 
 int /*<<< orphan*/  clock_adjust ; 

__attribute__((used)) static void
periodic_adjust(
		void
		)
{
	register long adjustment;

	adjustments++;

	adjustment = R_SHIFT(clock_adjust, PHASE_WEIGHT);

	clock_adjust -= adjustment;

	adjustment += R_SHIFT(accum_drift, USECSCALE+ADJINTERVAL);

	adj_time(adjustment);
}