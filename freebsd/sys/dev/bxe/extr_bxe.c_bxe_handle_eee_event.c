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
struct bxe_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOGD (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  DBG_INTR ; 
 int /*<<< orphan*/  DRV_MSG_CODE_EEE_RESULTS_ACK ; 
 int /*<<< orphan*/  bxe_fw_command (struct bxe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bxe_handle_eee_event(struct bxe_softc *sc)
{
    BLOGD(sc, DBG_INTR, "EEE - LLDP event\n");
    bxe_fw_command(sc, DRV_MSG_CODE_EEE_RESULTS_ACK, 0);
}