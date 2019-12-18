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
struct sleepqueue_chain {int /*<<< orphan*/  sc_lock; } ;

/* Variables and functions */
 struct sleepqueue_chain* SC_LOOKUP (void*) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 

void
sleepq_lock(void *wchan)
{
	struct sleepqueue_chain *sc;

	sc = SC_LOOKUP(wchan);
	mtx_lock_spin(&sc->sc_lock);
}