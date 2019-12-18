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
struct sc_cnstate {scalar_t__ kbd_locked; } ;
typedef  int /*<<< orphan*/  sc_softc_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sccnkbdunlock(sc_softc_t *sc, struct sc_cnstate *sp)
{
    if (sp->kbd_locked)
	mtx_unlock(&Giant);
    sp->kbd_locked = FALSE;
}