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
struct pthread {int dummy; } ;

/* Variables and functions */
 struct sleepqueue_chain* SC_LOOKUP (void*) ; 
 int /*<<< orphan*/  THR_LOCK_ACQUIRE_SPIN (struct pthread*,int /*<<< orphan*/ *) ; 
 struct pthread* _get_curthread () ; 

void
_sleepq_lock(void *wchan)
{
	struct pthread *curthread = _get_curthread();
	struct sleepqueue_chain *sc;

	sc = SC_LOOKUP(wchan);
	THR_LOCK_ACQUIRE_SPIN(curthread, &sc->sc_lock);
}