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
struct pci_pbm_info {unsigned long controller_regs; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned long SCHIZO_UEAFSR_AID ; 
 unsigned long SCHIZO_UEAFSR_BMSK ; 
 unsigned long SCHIZO_UEAFSR_ECCSYND ; 
 unsigned long SCHIZO_UEAFSR_ERRPNDG ; 
 unsigned long SCHIZO_UEAFSR_MTAG ; 
 unsigned long SCHIZO_UEAFSR_MTAGSYND ; 
 unsigned long SCHIZO_UEAFSR_OWNEDIN ; 
 unsigned long SCHIZO_UEAFSR_PARTIAL ; 
 unsigned long SCHIZO_UEAFSR_PDRD ; 
 unsigned long SCHIZO_UEAFSR_PDWR ; 
 unsigned long SCHIZO_UEAFSR_PPIO ; 
 unsigned long SCHIZO_UEAFSR_QOFF ; 
 unsigned long SCHIZO_UEAFSR_SDMA ; 
 unsigned long SCHIZO_UEAFSR_SPIO ; 
 unsigned long SCHIZO_UE_AFAR ; 
 unsigned long SCHIZO_UE_AFSR ; 
 int /*<<< orphan*/  UE_ERR ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  schizo_check_iommu_error (struct pci_pbm_info*,int /*<<< orphan*/ ) ; 
 unsigned long upa_readq (unsigned long) ; 
 int /*<<< orphan*/  upa_writeq (unsigned long,unsigned long) ; 

__attribute__((used)) static irqreturn_t schizo_ue_intr(int irq, void *dev_id)
{
	struct pci_pbm_info *pbm = dev_id;
	unsigned long afsr_reg = pbm->controller_regs + SCHIZO_UE_AFSR;
	unsigned long afar_reg = pbm->controller_regs + SCHIZO_UE_AFAR;
	unsigned long afsr, afar, error_bits;
	int reported, limit;

	/* Latch uncorrectable error status. */
	afar = upa_readq(afar_reg);

	/* If either of the error pending bits are set in the
	 * AFSR, the error status is being actively updated by
	 * the hardware and we must re-read to get a clean value.
	 */
	limit = 1000;
	do {
		afsr = upa_readq(afsr_reg);
	} while ((afsr & SCHIZO_UEAFSR_ERRPNDG) != 0 && --limit);

	/* Clear the primary/secondary error status bits. */
	error_bits = afsr &
		(SCHIZO_UEAFSR_PPIO | SCHIZO_UEAFSR_PDRD | SCHIZO_UEAFSR_PDWR |
		 SCHIZO_UEAFSR_SPIO | SCHIZO_UEAFSR_SDMA);
	if (!error_bits)
		return IRQ_NONE;
	upa_writeq(error_bits, afsr_reg);

	/* Log the error. */
	printk("%s: Uncorrectable Error, primary error type[%s]\n",
	       pbm->name,
	       (((error_bits & SCHIZO_UEAFSR_PPIO) ?
		 "PIO" :
		 ((error_bits & SCHIZO_UEAFSR_PDRD) ?
		  "DMA Read" :
		  ((error_bits & SCHIZO_UEAFSR_PDWR) ?
		   "DMA Write" : "???")))));
	printk("%s: bytemask[%04lx] qword_offset[%lx] SAFARI_AID[%02lx]\n",
	       pbm->name,
	       (afsr & SCHIZO_UEAFSR_BMSK) >> 32UL,
	       (afsr & SCHIZO_UEAFSR_QOFF) >> 30UL,
	       (afsr & SCHIZO_UEAFSR_AID) >> 24UL);
	printk("%s: partial[%d] owned_in[%d] mtag[%lx] mtag_synd[%lx] ecc_sync[%lx]\n",
	       pbm->name,
	       (afsr & SCHIZO_UEAFSR_PARTIAL) ? 1 : 0,
	       (afsr & SCHIZO_UEAFSR_OWNEDIN) ? 1 : 0,
	       (afsr & SCHIZO_UEAFSR_MTAG) >> 13UL,
	       (afsr & SCHIZO_UEAFSR_MTAGSYND) >> 16UL,
	       (afsr & SCHIZO_UEAFSR_ECCSYND) >> 0UL);
	printk("%s: UE AFAR [%016lx]\n", pbm->name, afar);
	printk("%s: UE Secondary errors [", pbm->name);
	reported = 0;
	if (afsr & SCHIZO_UEAFSR_SPIO) {
		reported++;
		printk("(PIO)");
	}
	if (afsr & SCHIZO_UEAFSR_SDMA) {
		reported++;
		printk("(DMA)");
	}
	if (!reported)
		printk("(none)");
	printk("]\n");

	/* Interrogate IOMMU for error status. */
	schizo_check_iommu_error(pbm, UE_ERR);

	return IRQ_HANDLED;
}