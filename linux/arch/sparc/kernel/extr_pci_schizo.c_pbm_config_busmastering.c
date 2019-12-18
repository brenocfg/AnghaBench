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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct pci_pbm_info {int /*<<< orphan*/  pci_first_busno; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 int /*<<< orphan*/  pci_config_write8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * schizo_pci_config_mkaddr (struct pci_pbm_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pbm_config_busmastering(struct pci_pbm_info *pbm)
{
	u8 *addr;

	/* Set cache-line size to 64 bytes, this is actually
	 * a nop but I do it for completeness.
	 */
	addr = schizo_pci_config_mkaddr(pbm, pbm->pci_first_busno,
					0, PCI_CACHE_LINE_SIZE);
	pci_config_write8(addr, 64 / sizeof(u32));

	/* Set PBM latency timer to 64 PCI clocks. */
	addr = schizo_pci_config_mkaddr(pbm, pbm->pci_first_busno,
					0, PCI_LATENCY_TIMER);
	pci_config_write8(addr, 64);
}