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
struct amr_softc {int /*<<< orphan*/  amr_busyslots; int /*<<< orphan*/ ** amr_busycmd; } ;
struct amr_command {int ac_slot; struct amr_softc* ac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static __inline int
amr_freeslot(struct amr_command *ac)
{
    struct amr_softc *sc = ac->ac_sc;
    int			slot;

    debug_called(3);

    slot = ac->ac_slot;
    if (sc->amr_busycmd[slot] == NULL)
	panic("amr: slot %d not busy?\n", slot);

    sc->amr_busycmd[slot] = NULL;
    atomic_subtract_int(&sc->amr_busyslots, 1);

    return (0);
}