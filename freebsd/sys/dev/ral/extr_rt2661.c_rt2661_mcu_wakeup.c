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
struct rt2661_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_WRITE (struct rt2661_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2661_IO_CNTL_CSR ; 
 int /*<<< orphan*/  RT2661_MAC_CSR11 ; 
 int /*<<< orphan*/  RT2661_MCU_CMD_WAKEUP ; 
 int /*<<< orphan*/  RT2661_PCI_USEC_CSR ; 
 int /*<<< orphan*/  RT2661_SOFT_RESET_CSR ; 
 int /*<<< orphan*/  rt2661_tx_cmd (struct rt2661_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rt2661_mcu_wakeup(struct rt2661_softc *sc)
{
	RAL_WRITE(sc, RT2661_MAC_CSR11, 5 << 16);

	RAL_WRITE(sc, RT2661_SOFT_RESET_CSR, 0x7);
	RAL_WRITE(sc, RT2661_IO_CNTL_CSR, 0x18);
	RAL_WRITE(sc, RT2661_PCI_USEC_CSR, 0x20);

	/* send wakeup command to MCU */
	rt2661_tx_cmd(sc, RT2661_MCU_CMD_WAKEUP, 0);
}