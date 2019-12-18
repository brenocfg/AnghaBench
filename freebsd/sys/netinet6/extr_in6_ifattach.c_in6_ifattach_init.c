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
 int /*<<< orphan*/  V_in6_tmpaddrtimer_ch ; 
 int V_ip6_desync_factor ; 
 int V_ip6_temp_preferred_lifetime ; 
 int V_ip6_temp_regen_advance ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curvnet ; 
 int hz ; 
 int /*<<< orphan*/  in6_tmpaddrtimer ; 

__attribute__((used)) static void
in6_ifattach_init(void *dummy)
{

	/* Timer for regeneranation of temporary addresses randomize ID. */
	callout_init(&V_in6_tmpaddrtimer_ch, 0);
	callout_reset(&V_in6_tmpaddrtimer_ch,
	    (V_ip6_temp_preferred_lifetime - V_ip6_desync_factor -
	    V_ip6_temp_regen_advance) * hz,
	    in6_tmpaddrtimer, curvnet);
}