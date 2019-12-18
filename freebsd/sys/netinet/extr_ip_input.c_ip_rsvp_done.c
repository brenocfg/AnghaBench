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
 scalar_t__ V_ip_rsvp_on ; 
 int /*<<< orphan*/ * V_ip_rsvpd ; 
 int /*<<< orphan*/  V_rsvp_on ; 

int
ip_rsvp_done(void)
{

	V_ip_rsvpd = NULL;
	/*
	 * This may seem silly, but we need to be sure we don't over-decrement
	 * the RSVP counter, in case something slips up.
	 */
	if (V_ip_rsvp_on) {
		V_ip_rsvp_on = 0;
		V_rsvp_on--;
	}
	return 0;
}