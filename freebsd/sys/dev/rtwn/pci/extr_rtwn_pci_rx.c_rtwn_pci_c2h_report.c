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
struct rtwn_pci_softc {int /*<<< orphan*/  pc_rx_buf; int /*<<< orphan*/  pc_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtwn_handle_c2h_report (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
rtwn_pci_c2h_report(struct rtwn_pci_softc *pc, int len)
{
	rtwn_handle_c2h_report(&pc->pc_sc, pc->pc_rx_buf, len);
}