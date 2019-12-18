#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int start; int end; } ;
struct TYPE_3__ {unsigned long m64_segsize; int m64_base; scalar_t__ reserved_pe_idx; int total_pe_num; } ;
struct pnv_phb {int /*<<< orphan*/  opal_id; TYPE_2__* hose; TYPE_1__ ioda; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {int /*<<< orphan*/  global_number; struct resource* mem_resources; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  OPAL_DISABLE_M64 ; 
 int /*<<< orphan*/  OPAL_ENABLE_M64_SPLIT ; 
 int /*<<< orphan*/  OPAL_M64_WINDOW_TYPE ; 
 scalar_t__ OPAL_SUCCESS ; 
 int PNV_IODA1_M64_NUM ; 
 int PNV_IODA1_M64_SEGS ; 
 int /*<<< orphan*/  WARN (int,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ opal_pci_phb_mmio_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ opal_pci_set_phb_mem_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pnv_ioda1_init_m64(struct pnv_phb *phb)
{
	struct resource *r;
	int index;

	/*
	 * There are 16 M64 BARs, each of which has 8 segments. So
	 * there are as many M64 segments as the maximum number of
	 * PEs, which is 128.
	 */
	for (index = 0; index < PNV_IODA1_M64_NUM; index++) {
		unsigned long base, segsz = phb->ioda.m64_segsize;
		int64_t rc;

		base = phb->ioda.m64_base +
		       index * PNV_IODA1_M64_SEGS * segsz;
		rc = opal_pci_set_phb_mem_window(phb->opal_id,
				OPAL_M64_WINDOW_TYPE, index, base, 0,
				PNV_IODA1_M64_SEGS * segsz);
		if (rc != OPAL_SUCCESS) {
			pr_warn("  Error %lld setting M64 PHB#%x-BAR#%d\n",
				rc, phb->hose->global_number, index);
			goto fail;
		}

		rc = opal_pci_phb_mmio_enable(phb->opal_id,
				OPAL_M64_WINDOW_TYPE, index,
				OPAL_ENABLE_M64_SPLIT);
		if (rc != OPAL_SUCCESS) {
			pr_warn("  Error %lld enabling M64 PHB#%x-BAR#%d\n",
				rc, phb->hose->global_number, index);
			goto fail;
		}
	}

	/*
	 * Exclude the segments for reserved and root bus PE, which
	 * are first or last two PEs.
	 */
	r = &phb->hose->mem_resources[1];
	if (phb->ioda.reserved_pe_idx == 0)
		r->start += (2 * phb->ioda.m64_segsize);
	else if (phb->ioda.reserved_pe_idx == (phb->ioda.total_pe_num - 1))
		r->end -= (2 * phb->ioda.m64_segsize);
	else
		WARN(1, "Wrong reserved PE#%x on PHB#%x\n",
		     phb->ioda.reserved_pe_idx, phb->hose->global_number);

	return 0;

fail:
	for ( ; index >= 0; index--)
		opal_pci_phb_mmio_enable(phb->opal_id,
			OPAL_M64_WINDOW_TYPE, index, OPAL_DISABLE_M64);

	return -EIO;
}