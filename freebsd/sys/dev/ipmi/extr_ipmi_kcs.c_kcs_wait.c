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
struct ipmi_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int INB (struct ipmi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KCS_CTL_STS ; 
 int MAX_TIMEOUT ; 
 int POLLING_DELAY_MAX ; 
 int POLLING_DELAY_MIN ; 
 int ticks ; 

__attribute__((used)) static int
kcs_wait(struct ipmi_softc *sc, int value, int mask)
{
	int status, start = ticks;
	int delay_usec = POLLING_DELAY_MIN;

	status = INB(sc, KCS_CTL_STS);
	while (ticks - start < MAX_TIMEOUT && (status & mask) != value) {
		/*
		 * The wait delay is increased exponentially to avoid putting
		 * significant load on I/O bus.
		 */
		DELAY(delay_usec);
		status = INB(sc, KCS_CTL_STS);
		if (delay_usec < POLLING_DELAY_MAX)
			delay_usec *= 2;
	}
	return (status);
}