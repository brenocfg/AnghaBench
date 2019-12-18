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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {scalar_t__ num; } ;
struct ps2kbd_softc {int /*<<< orphan*/  atkbdc_sc; int /*<<< orphan*/  mtx; TYPE_1__ fifo; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 scalar_t__ PS2KBD_FIFOSZ ; 
 int /*<<< orphan*/  atkbdc_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ps2kbd_keysym_queue (struct ps2kbd_softc*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ps2kbd_event(int down, uint32_t keysym, void *arg)
{
	struct ps2kbd_softc *sc = arg;
	int fifo_full;

	pthread_mutex_lock(&sc->mtx);
	if (!sc->enabled) {
		pthread_mutex_unlock(&sc->mtx);
		return;
	}
	fifo_full = sc->fifo.num == PS2KBD_FIFOSZ;
	ps2kbd_keysym_queue(sc, down, keysym);
	pthread_mutex_unlock(&sc->mtx);

	if (!fifo_full)
		atkbdc_event(sc->atkbdc_sc, 1);
}