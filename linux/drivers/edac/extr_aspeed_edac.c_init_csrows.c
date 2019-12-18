#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int start; } ;
struct mem_ctl_info {int /*<<< orphan*/  pdev; struct csrow_info** csrows; } ;
struct dimm_info {int mtype; int nr_pages; int /*<<< orphan*/  edac_mode; } ;
struct device_node {int dummy; } ;
struct csrow_info {int first_page; int last_page; int nr_channels; TYPE_1__** channels; } ;
struct TYPE_2__ {struct dimm_info* dimm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASPEED_MCR_CONF ; 
 int ASPEED_MCR_CONF_DRAM_TYPE ; 
 int /*<<< orphan*/  EDAC_SECDED ; 
 int ENODEV ; 
 int MEM_DDR3 ; 
 int MEM_DDR4 ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  aspeed_regmap ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 struct device_node* of_find_node_by_path (char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int resource_size (struct resource*) ; 

__attribute__((used)) static int init_csrows(struct mem_ctl_info *mci)
{
	struct csrow_info *csrow = mci->csrows[0];
	u32 nr_pages, dram_type;
	struct dimm_info *dimm;
	struct device_node *np;
	struct resource r;
	u32 reg04;
	int rc;

	/* retrieve info about physical memory from device tree */
	np = of_find_node_by_path("/memory");
	if (!np) {
		dev_err(mci->pdev, "dt: missing /memory node\n");
		return -ENODEV;
	};

	rc = of_address_to_resource(np, 0, &r);

	of_node_put(np);

	if (rc) {
		dev_err(mci->pdev, "dt: failed requesting resource for /memory node\n");
		return rc;
	};

	dev_dbg(mci->pdev, "dt: /memory node resources: first page r.start=0x%x, resource_size=0x%x, PAGE_SHIFT macro=0x%x\n",
		r.start, resource_size(&r), PAGE_SHIFT);

	csrow->first_page = r.start >> PAGE_SHIFT;
	nr_pages = resource_size(&r) >> PAGE_SHIFT;
	csrow->last_page = csrow->first_page + nr_pages - 1;

	regmap_read(aspeed_regmap, ASPEED_MCR_CONF, &reg04);
	dram_type = (reg04 & ASPEED_MCR_CONF_DRAM_TYPE) ? MEM_DDR4 : MEM_DDR3;

	dimm = csrow->channels[0]->dimm;
	dimm->mtype = dram_type;
	dimm->edac_mode = EDAC_SECDED;
	dimm->nr_pages = nr_pages / csrow->nr_channels;

	dev_dbg(mci->pdev, "initialized dimm with first_page=0x%lx and nr_pages=0x%x\n",
		csrow->first_page, nr_pages);

	return 0;
}