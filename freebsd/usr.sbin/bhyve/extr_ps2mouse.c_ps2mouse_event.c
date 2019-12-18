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
typedef  int uint8_t ;
struct TYPE_2__ {scalar_t__ num; } ;
struct ps2mouse_softc {int status; int /*<<< orphan*/  atkbdc_sc; TYPE_1__ fifo; int /*<<< orphan*/  mtx; int /*<<< orphan*/  ctrlenable; } ;

/* Variables and functions */
 int PS2M_STS_ENABLE_DEV ; 
 int PS2M_STS_LEFT_BUTTON ; 
 int PS2M_STS_MID_BUTTON ; 
 int PS2M_STS_RIGHT_BUTTON ; 
 int /*<<< orphan*/  atkbdc_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  movement_get (struct ps2mouse_softc*) ; 
 int /*<<< orphan*/  movement_update (struct ps2mouse_softc*,int,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ps2mouse_event(uint8_t button, int x, int y, void *arg)
{
	struct ps2mouse_softc *sc = arg;

	pthread_mutex_lock(&sc->mtx);
	movement_update(sc, x, y);

	sc->status &= ~(PS2M_STS_LEFT_BUTTON |
	    PS2M_STS_RIGHT_BUTTON | PS2M_STS_MID_BUTTON);
	if (button & (1 << 0))
		sc->status |= PS2M_STS_LEFT_BUTTON;
	if (button & (1 << 1))
		sc->status |= PS2M_STS_MID_BUTTON;
	if (button & (1 << 2))
		sc->status |= PS2M_STS_RIGHT_BUTTON;

	if ((sc->status & PS2M_STS_ENABLE_DEV) == 0 || !sc->ctrlenable) {
		/* no data reporting */
		pthread_mutex_unlock(&sc->mtx);
		return;
	}

	movement_get(sc);
	pthread_mutex_unlock(&sc->mtx);

	if (sc->fifo.num > 0)
		atkbdc_event(sc->atkbdc_sc, 0);
}