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
typedef  int /*<<< orphan*/  uint64_t ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETLOGIC_IO_PCIX_OFFSET ; 
 int /*<<< orphan*/  nlm_mmio_base (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_read_reg (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void xlr_pci_ack(struct irq_data *d)
{
	uint64_t pcibase = nlm_mmio_base(NETLOGIC_IO_PCIX_OFFSET);

	nlm_read_reg(pcibase, (0x140 >> 2));
}