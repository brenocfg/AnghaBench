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
struct emu_sc_info {scalar_t__* timer; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ EMU_MAX_IRQ_CONSUMERS ; 
 int /*<<< orphan*/  RANGE (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  emu_timer_enable (struct emu_sc_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
emu_timer_clear(struct emu_sc_info *sc, int timer)
{
	if (timer < 0)
		return (-1);

	RANGE(timer, 0, EMU_MAX_IRQ_CONSUMERS-1);

	emu_timer_enable(sc, timer, 0);

	mtx_lock(&sc->lock);
	if (sc->timer[timer] != 0)
		sc->timer[timer] = 0;
	mtx_unlock(&sc->lock);

	return (timer);
}