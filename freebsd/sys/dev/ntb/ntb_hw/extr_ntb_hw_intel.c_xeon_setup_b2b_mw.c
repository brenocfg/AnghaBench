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
typedef  int vm_size_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ntb_softc {scalar_t__ b2b_mw_idx; int b2b_off; scalar_t__ msix_mw_idx; struct ntb_pci_bar_info* bar_info; struct ntb_pci_bar_info* peer_lapic_bar; void* msix_xlat; int /*<<< orphan*/  device; } ;
struct ntb_pci_bar_info {int size; } ;
struct ntb_b2b_addr {int bar0_addr; int bar2_addr64; int bar4_addr64; int bar4_addr32; int bar5_addr32; } ;
typedef  enum ntb_bar { ____Placeholder_ntb_bar } ntb_bar ;

/* Variables and functions */
 scalar_t__ B2B_MW_DISABLED ; 
 int EIO ; 
 scalar_t__ HAS_FEATURE (struct ntb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MSI_INTEL_ADDR_BASE ; 
 int NTB_B2B_BAR_1 ; 
 int NTB_B2B_BAR_2 ; 
 int NTB_B2B_BAR_3 ; 
 int NTB_CONFIG_BAR ; 
 int NTB_MAX_BARS ; 
 int /*<<< orphan*/  NTB_SB01BASE_LOCKUP ; 
 int /*<<< orphan*/  NTB_SPLIT_BAR ; 
 int XEON_B2B_MIN_SIZE ; 
 int /*<<< orphan*/  XEON_B2B_XLAT_OFFSETL ; 
 int /*<<< orphan*/  XEON_B2B_XLAT_OFFSETU ; 
 int /*<<< orphan*/  XEON_PBAR2LMT_OFFSET ; 
 int /*<<< orphan*/  XEON_PBAR4LMT_OFFSET ; 
 int /*<<< orphan*/  XEON_SBAR0BASE_OFFSET ; 
 int /*<<< orphan*/  XEON_SBAR2XLAT_OFFSET ; 
 int /*<<< orphan*/  XEON_SBAR4XLAT_OFFSET ; 
 int /*<<< orphan*/  bar_get_xlat_params (struct ntb_softc*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bar_is_64bit (struct ntb_softc*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int intel_ntb_mw_to_bar (struct ntb_softc*,scalar_t__) ; 
 void* intel_ntb_reg_read (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ntb_reg_write (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ntb_b2b_mw_share ; 
 int /*<<< orphan*/  xeon_reset_sbar_size (struct ntb_softc*,int,int) ; 
 int /*<<< orphan*/  xeon_set_pbar_xlat (struct ntb_softc*,int,int) ; 
 int /*<<< orphan*/  xeon_set_sbar_base_and_limit (struct ntb_softc*,int,int,int) ; 

__attribute__((used)) static int
xeon_setup_b2b_mw(struct ntb_softc *ntb, const struct ntb_b2b_addr *addr,
    const struct ntb_b2b_addr *peer_addr)
{
	struct ntb_pci_bar_info *b2b_bar;
	vm_size_t bar_size;
	uint64_t bar_addr;
	enum ntb_bar b2b_bar_num, i;

	if (ntb->b2b_mw_idx == B2B_MW_DISABLED) {
		b2b_bar = NULL;
		b2b_bar_num = NTB_CONFIG_BAR;
		ntb->b2b_off = 0;
	} else {
		b2b_bar_num = intel_ntb_mw_to_bar(ntb, ntb->b2b_mw_idx);
		KASSERT(b2b_bar_num > 0 && b2b_bar_num < NTB_MAX_BARS,
		    ("invalid b2b mw bar"));

		b2b_bar = &ntb->bar_info[b2b_bar_num];
		bar_size = b2b_bar->size;

		if (ntb_b2b_mw_share != 0 &&
		    (bar_size >> 1) >= XEON_B2B_MIN_SIZE)
			ntb->b2b_off = bar_size >> 1;
		else if (bar_size >= XEON_B2B_MIN_SIZE) {
			ntb->b2b_off = 0;
		} else {
			device_printf(ntb->device,
			    "B2B bar size is too small!\n");
			return (EIO);
		}
	}

	/*
	 * Reset the secondary bar sizes to match the primary bar sizes.
	 * (Except, disable or halve the size of the B2B secondary bar.)
	 */
	for (i = NTB_B2B_BAR_1; i < NTB_MAX_BARS; i++)
		xeon_reset_sbar_size(ntb, i, b2b_bar_num);

	bar_addr = 0;
	if (b2b_bar_num == NTB_CONFIG_BAR)
		bar_addr = addr->bar0_addr;
	else if (b2b_bar_num == NTB_B2B_BAR_1)
		bar_addr = addr->bar2_addr64;
	else if (b2b_bar_num == NTB_B2B_BAR_2 && !HAS_FEATURE(ntb, NTB_SPLIT_BAR))
		bar_addr = addr->bar4_addr64;
	else if (b2b_bar_num == NTB_B2B_BAR_2)
		bar_addr = addr->bar4_addr32;
	else if (b2b_bar_num == NTB_B2B_BAR_3)
		bar_addr = addr->bar5_addr32;
	else
		KASSERT(false, ("invalid bar"));

	intel_ntb_reg_write(8, XEON_SBAR0BASE_OFFSET, bar_addr);

	/*
	 * Other SBARs are normally hit by the PBAR xlat, except for the b2b
	 * register BAR.  The B2B BAR is either disabled above or configured
	 * half-size.  It starts at PBAR xlat + offset.
	 *
	 * Also set up incoming BAR limits == base (zero length window).
	 */
	xeon_set_sbar_base_and_limit(ntb, addr->bar2_addr64, NTB_B2B_BAR_1,
	    b2b_bar_num);
	if (HAS_FEATURE(ntb, NTB_SPLIT_BAR)) {
		xeon_set_sbar_base_and_limit(ntb, addr->bar4_addr32,
		    NTB_B2B_BAR_2, b2b_bar_num);
		xeon_set_sbar_base_and_limit(ntb, addr->bar5_addr32,
		    NTB_B2B_BAR_3, b2b_bar_num);
	} else
		xeon_set_sbar_base_and_limit(ntb, addr->bar4_addr64,
		    NTB_B2B_BAR_2, b2b_bar_num);

	/* Zero incoming translation addrs */
	intel_ntb_reg_write(8, XEON_SBAR2XLAT_OFFSET, 0);
	intel_ntb_reg_write(8, XEON_SBAR4XLAT_OFFSET, 0);

	if (HAS_FEATURE(ntb, NTB_SB01BASE_LOCKUP)) {
		uint32_t xlat_reg, lmt_reg;
		enum ntb_bar bar_num;

		/*
		 * We point the chosen MSIX MW BAR xlat to remote LAPIC for
		 * workaround
		 */
		bar_num = intel_ntb_mw_to_bar(ntb, ntb->msix_mw_idx);
		bar_get_xlat_params(ntb, bar_num, NULL, &xlat_reg, &lmt_reg);
		if (bar_is_64bit(ntb, bar_num)) {
			intel_ntb_reg_write(8, xlat_reg, MSI_INTEL_ADDR_BASE);
			ntb->msix_xlat = intel_ntb_reg_read(8, xlat_reg);
			intel_ntb_reg_write(8, lmt_reg, 0);
		} else {
			intel_ntb_reg_write(4, xlat_reg, MSI_INTEL_ADDR_BASE);
			ntb->msix_xlat = intel_ntb_reg_read(4, xlat_reg);
			intel_ntb_reg_write(4, lmt_reg, 0);
		}

		ntb->peer_lapic_bar =  &ntb->bar_info[bar_num];
	}
	(void)intel_ntb_reg_read(8, XEON_SBAR2XLAT_OFFSET);
	(void)intel_ntb_reg_read(8, XEON_SBAR4XLAT_OFFSET);

	/* Zero outgoing translation limits (whole bar size windows) */
	intel_ntb_reg_write(8, XEON_PBAR2LMT_OFFSET, 0);
	intel_ntb_reg_write(8, XEON_PBAR4LMT_OFFSET, 0);

	/* Set outgoing translation offsets */
	xeon_set_pbar_xlat(ntb, peer_addr->bar2_addr64, NTB_B2B_BAR_1);
	if (HAS_FEATURE(ntb, NTB_SPLIT_BAR)) {
		xeon_set_pbar_xlat(ntb, peer_addr->bar4_addr32, NTB_B2B_BAR_2);
		xeon_set_pbar_xlat(ntb, peer_addr->bar5_addr32, NTB_B2B_BAR_3);
	} else
		xeon_set_pbar_xlat(ntb, peer_addr->bar4_addr64, NTB_B2B_BAR_2);

	/* Set the translation offset for B2B registers */
	bar_addr = 0;
	if (b2b_bar_num == NTB_CONFIG_BAR)
		bar_addr = peer_addr->bar0_addr;
	else if (b2b_bar_num == NTB_B2B_BAR_1)
		bar_addr = peer_addr->bar2_addr64;
	else if (b2b_bar_num == NTB_B2B_BAR_2 && !HAS_FEATURE(ntb, NTB_SPLIT_BAR))
		bar_addr = peer_addr->bar4_addr64;
	else if (b2b_bar_num == NTB_B2B_BAR_2)
		bar_addr = peer_addr->bar4_addr32;
	else if (b2b_bar_num == NTB_B2B_BAR_3)
		bar_addr = peer_addr->bar5_addr32;
	else
		KASSERT(false, ("invalid bar"));

	/*
	 * B2B_XLAT_OFFSET is a 64-bit register but can only be written 32 bits
	 * at a time.
	 */
	intel_ntb_reg_write(4, XEON_B2B_XLAT_OFFSETL, bar_addr & 0xffffffff);
	intel_ntb_reg_write(4, XEON_B2B_XLAT_OFFSETU, bar_addr >> 32);
	return (0);
}