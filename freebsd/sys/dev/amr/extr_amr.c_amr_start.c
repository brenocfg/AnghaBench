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
struct amr_softc {int /*<<< orphan*/  amr_busyslots; struct amr_command** amr_busycmd; } ;
struct amr_command {int ac_slot; int /*<<< orphan*/  ac_flags; struct amr_softc* ac_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMR_CMD_BUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  amr_freeslot (struct amr_command*) ; 
 int amr_mapcmd (struct amr_command*) ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  debug_called (int) ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static int
amr_start(struct amr_command *ac)
{
    struct amr_softc *sc;
    int error = 0;
    int slot;

    debug_called(3);

    /* mark command as busy so that polling consumer can tell */
    sc = ac->ac_sc;
    ac->ac_flags |= AMR_CMD_BUSY;

    /* get a command slot (freed in amr_done) */
    slot = ac->ac_slot;
    if (sc->amr_busycmd[slot] != NULL)
	panic("amr: slot %d busy?\n", slot);
    sc->amr_busycmd[slot] = ac;
    atomic_add_int(&sc->amr_busyslots, 1);

    /* Now we have a slot, we can map the command (unmapped in amr_complete). */
    if ((error = amr_mapcmd(ac)) == ENOMEM) {
	/*
	 * Memory resources are short, so free the slot and let this be tried
	 * later.
	 */
	amr_freeslot(ac);
    }

    return (error);
}