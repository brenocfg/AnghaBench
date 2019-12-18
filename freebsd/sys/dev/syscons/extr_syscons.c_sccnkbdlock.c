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
struct sc_cnstate {int kbd_locked; } ;
typedef  int /*<<< orphan*/  sc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  kdb_active ; 
 scalar_t__ mtx_trylock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sccnkbdlock(sc_softc_t *sc, struct sc_cnstate *sp)
{
    /*
     * Locking method: hope for the best.
     * The keyboard is supposed to be Giant locked.  We can't handle that
     * in general.  The kdb_active case here is not safe, and we will
     * proceed without the lock in all cases.
     */
    sp->kbd_locked = !kdb_active && mtx_trylock(&Giant);
}