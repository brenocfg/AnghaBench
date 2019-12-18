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
struct ahd_softc {int /*<<< orphan*/  hs_mailbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENINT_COALESCE ; 
 int /*<<< orphan*/  HS_MAILBOX ; 
 int /*<<< orphan*/  ahd_flush_device_writes (struct ahd_softc*) ; 
 int /*<<< orphan*/  ahd_outb (struct ahd_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ahd_run_qoutfifo (struct ahd_softc*) ; 

void
ahd_enable_coalescing(struct ahd_softc *ahd, int enable)
{

	ahd->hs_mailbox &= ~ENINT_COALESCE;
	if (enable)
		ahd->hs_mailbox |= ENINT_COALESCE;
	ahd_outb(ahd, HS_MAILBOX, ahd->hs_mailbox);
	ahd_flush_device_writes(ahd);
	ahd_run_qoutfifo(ahd);
}