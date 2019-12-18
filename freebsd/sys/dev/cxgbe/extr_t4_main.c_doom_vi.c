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
struct vi_info {int dummy; } ;
struct adapter {char* last_op; scalar_t__ last_op_flags; int /*<<< orphan*/  last_op_thr; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_LOCK (struct adapter*) ; 
 int /*<<< orphan*/  ADAPTER_UNLOCK (struct adapter*) ; 
 scalar_t__ IS_BUSY (struct adapter*) ; 
 int /*<<< orphan*/  SET_BUSY (struct adapter*) ; 
 int /*<<< orphan*/  SET_DOOMED (struct vi_info*) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  mtx_sleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
doom_vi(struct adapter *sc, struct vi_info *vi)
{

	ADAPTER_LOCK(sc);
	SET_DOOMED(vi);
	wakeup(&sc->flags);
	while (IS_BUSY(sc))
		mtx_sleep(&sc->flags, &sc->sc_lock, 0, "t4detach", 0);
	SET_BUSY(sc);
#ifdef INVARIANTS
	sc->last_op = "t4detach";
	sc->last_op_thr = curthread;
	sc->last_op_flags = 0;
#endif
	ADAPTER_UNLOCK(sc);
}