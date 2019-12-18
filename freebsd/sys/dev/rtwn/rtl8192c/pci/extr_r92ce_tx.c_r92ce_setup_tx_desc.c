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
typedef  int /*<<< orphan*/  uint32_t ;
struct rtwn_pci_softc {int dummy; } ;
struct r92ce_tx_desc {int /*<<< orphan*/  nextdescaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

void
r92ce_setup_tx_desc(struct rtwn_pci_softc *pc, void *desc,
    uint32_t next_desc_addr)
{
	struct r92ce_tx_desc *txd = desc;

	/* setup tx desc */
	txd->nextdescaddr = htole32(next_desc_addr);
}