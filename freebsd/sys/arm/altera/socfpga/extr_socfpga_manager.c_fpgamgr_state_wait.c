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
struct fpgamgr_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int fpgamgr_state_get (struct fpgamgr_softc*) ; 

__attribute__((used)) static int
fpgamgr_state_wait(struct fpgamgr_softc *sc, int state)
{
	int tout;

	tout = 1000;
	while (tout > 0) {
		if (fpgamgr_state_get(sc) == state)
			break;
		tout--;
		DELAY(10);
	}
	if (tout == 0) {
		return (1);
	}

	return (0);
}