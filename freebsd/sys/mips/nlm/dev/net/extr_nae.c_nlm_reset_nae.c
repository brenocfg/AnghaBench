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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  NAE_RX_CONFIG ; 
 int /*<<< orphan*/  SYS_RESET ; 
 int /*<<< orphan*/  XLP_PCI_CFGREG4 ; 
 int /*<<< orphan*/  nlm_get_nae_pcibase (int) ; 
 int /*<<< orphan*/  nlm_get_nae_regbase (int) ; 
 int /*<<< orphan*/  nlm_get_sys_regbase (int) ; 
 scalar_t__ nlm_is_xlp3xx () ; 
 scalar_t__ nlm_is_xlp8xx_ax () ; 
 int nlm_read_nae_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nlm_read_pci_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlm_write_pci_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nlm_write_sys_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
nlm_reset_nae(int node)
{
	uint64_t sysbase;
	uint64_t nae_base;
	uint64_t nae_pcibase;
	uint32_t rx_config;
	uint32_t bar0;
	int reset_bit;

	sysbase  = nlm_get_sys_regbase(node);
	nae_base = nlm_get_nae_regbase(node);
	nae_pcibase = nlm_get_nae_pcibase(node);

	bar0 = nlm_read_pci_reg(nae_pcibase, XLP_PCI_CFGREG4);

#if BYTE_ORDER == LITTLE_ENDIAN
	if (nlm_is_xlp8xx_ax()) {
		uint8_t	val;
		/* membar fixup */
		val = (bar0 >> 24) & 0xff;
		bar0 = (val << 24) | (val << 16) | (val << 8) | val;
	}
#endif

	if (nlm_is_xlp3xx())
		reset_bit = 6;
	else
		reset_bit = 9;

	/* Reset NAE */
	nlm_write_sys_reg(sysbase, SYS_RESET, (1 << reset_bit));

	/* XXXJC - 1s delay here may be too high */
	DELAY(1000000);
	nlm_write_sys_reg(sysbase, SYS_RESET, (0 << reset_bit));
	DELAY(1000000);

	rx_config = nlm_read_nae_reg(nae_base, NAE_RX_CONFIG);
	nlm_write_pci_reg(nae_pcibase, XLP_PCI_CFGREG4, bar0);
}