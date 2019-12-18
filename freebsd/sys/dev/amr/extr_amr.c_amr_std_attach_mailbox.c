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
struct amr_softc {int amr_mailboxphys; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMR_SACK_INTERRUPT (struct amr_softc*) ; 
 int /*<<< orphan*/  AMR_SBYTE_SET (struct amr_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AMR_SENABLE_INTR (struct amr_softc*) ; 
 int /*<<< orphan*/  AMR_SMBOX_0 ; 
 int /*<<< orphan*/  AMR_SMBOX_1 ; 
 int /*<<< orphan*/  AMR_SMBOX_2 ; 
 int /*<<< orphan*/  AMR_SMBOX_3 ; 
 int AMR_SMBOX_ADDR ; 
 int /*<<< orphan*/  AMR_SMBOX_ENABLE ; 

__attribute__((used)) static void
amr_std_attach_mailbox(struct amr_softc *sc)
{

    /* program the mailbox physical address */
    AMR_SBYTE_SET(sc, AMR_SMBOX_0, sc->amr_mailboxphys         & 0xff);
    AMR_SBYTE_SET(sc, AMR_SMBOX_1, (sc->amr_mailboxphys >>  8) & 0xff);
    AMR_SBYTE_SET(sc, AMR_SMBOX_2, (sc->amr_mailboxphys >> 16) & 0xff);
    AMR_SBYTE_SET(sc, AMR_SMBOX_3, (sc->amr_mailboxphys >> 24) & 0xff);
    AMR_SBYTE_SET(sc, AMR_SMBOX_ENABLE, AMR_SMBOX_ADDR);

    /* clear any outstanding interrupt and enable interrupts proper */
    AMR_SACK_INTERRUPT(sc);
    AMR_SENABLE_INTR(sc);
}