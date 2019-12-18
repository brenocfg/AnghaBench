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
struct emu_sc_info {int* timer; scalar_t__ timerinterval; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EMU_MAX_IRQ_CONSUMERS ; 
 int /*<<< orphan*/  EMU_TIMER ; 
 int /*<<< orphan*/  RANGE (int,int,int) ; 
 int /*<<< orphan*/  emu_wr (struct emu_sc_info*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
emu_timer_set(struct emu_sc_info *sc, int timer, int delay)
{
	int i;

	if (timer < 0)
		return (-1);

	RANGE(delay, 16, 1024);
	RANGE(timer, 0, EMU_MAX_IRQ_CONSUMERS-1);

	mtx_lock(&sc->lock);
	sc->timer[timer] = delay;
	for (i = 0; i < EMU_MAX_IRQ_CONSUMERS; i++)
		if (sc->timerinterval > sc->timer[i])
			sc->timerinterval = sc->timer[i];

	/* XXX */
	emu_wr(sc, EMU_TIMER, sc->timerinterval & 0x03ff, 2);
	mtx_unlock(&sc->lock);

	return (timer);
}