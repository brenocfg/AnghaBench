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
struct TYPE_2__ {int type; void* get_width; void* interleave_pkg; void* interleave_list; void* max_sad; void* dram_attr; void* interleave_mode; void* sad_limit; int /*<<< orphan*/ * rir_limit; void* get_ha; void* get_node_id; void* get_memory_type; struct edac_mc_layer* dram_rule; void* get_tohm; void* get_tolm; int /*<<< orphan*/  rankcfgr; } ;
struct sbridge_pvt {struct sbridge_dev* sbridge_dev; TYPE_1__ info; } ;
struct sbridge_dev {struct mem_ctl_info* mci; int /*<<< orphan*/  dom; int /*<<< orphan*/  source_id; int /*<<< orphan*/  mc; struct pci_dev** pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct mem_ctl_info {void* ctl_name; int /*<<< orphan*/ * pdev; int /*<<< orphan*/ * ctl_page_to_phys; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  mod_name; void* edac_cap; void* edac_ctl_cap; int /*<<< orphan*/  mtype_cap; struct sbridge_pvt* pvt_info; } ;
struct edac_mc_layer {int size; int is_virt_csrow; int /*<<< orphan*/  type; } ;
typedef  enum type { ____Placeholder_type } type ;

/* Variables and functions */
 void* ARRAY_SIZE (struct edac_mc_layer*) ; 
#define  BROADWELL 132 
 void* EDAC_FLAG_NONE ; 
 int /*<<< orphan*/  EDAC_MC_LAYER_CHANNEL ; 
 int /*<<< orphan*/  EDAC_MC_LAYER_SLOT ; 
 int /*<<< orphan*/  EDAC_MOD_STR ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  HASWELL 131 
 int /*<<< orphan*/  IB_RANK_CFG_A ; 
#define  IVY_BRIDGE 130 
#define  KNIGHTS_LANDING 129 
 int KNL_MAX_CHANNELS ; 
 int MAX_DIMMS ; 
 int /*<<< orphan*/  MEM_FLAG_DDR3 ; 
 int /*<<< orphan*/  MEM_FLAG_DDR4 ; 
 int NUM_CHANNELS ; 
#define  SANDY_BRIDGE 128 
 int /*<<< orphan*/  SB_RANK_CFG_A ; 
 void* broadwell_get_width ; 
 int broadwell_mci_bind_devs (struct mem_ctl_info*,struct sbridge_dev*) ; 
 void* dram_attr ; 
 void* dram_attr_knl ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int edac_mc_add_mc (struct mem_ctl_info*) ; 
 struct mem_ctl_info* edac_mc_alloc (int /*<<< orphan*/ ,void*,struct edac_mc_layer*,int) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 int get_dimm_config (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  get_memory_layout (struct mem_ctl_info*) ; 
 void* get_memory_type ; 
 void* get_node_id ; 
 int /*<<< orphan*/  get_source_id (struct mem_ctl_info*) ; 
 void* haswell_get_memory_type ; 
 void* haswell_get_node_id ; 
 void* haswell_get_tohm ; 
 void* haswell_get_tolm ; 
 int haswell_mci_bind_devs (struct mem_ctl_info*,struct sbridge_dev*) ; 
 void* haswell_rir_limit ; 
 struct edac_mc_layer* ibridge_dram_rule ; 
 void* ibridge_get_ha ; 
 void* ibridge_get_tohm ; 
 void* ibridge_get_tolm ; 
 void* ibridge_get_width ; 
 void* ibridge_interleave_list ; 
 void* ibridge_interleave_pkg ; 
 int ibridge_mci_bind_devs (struct mem_ctl_info*,struct sbridge_dev*) ; 
 void* interleave_mode ; 
 void* kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 struct edac_mc_layer* knl_dram_rule ; 
 void* knl_get_ha ; 
 void* knl_get_memory_type ; 
 void* knl_get_node_id ; 
 void* knl_get_tohm ; 
 void* knl_get_tolm ; 
 void* knl_get_width ; 
 void* knl_interleave_list ; 
 void* knl_interleave_mode ; 
 int knl_mci_bind_devs (struct mem_ctl_info*,struct sbridge_dev*) ; 
 void* knl_sad_limit ; 
 int /*<<< orphan*/  memset (struct sbridge_pvt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 void* rir_limit ; 
 void* sad_limit ; 
 struct edac_mc_layer* sbridge_dram_rule ; 
 void* sbridge_get_ha ; 
 void* sbridge_get_tohm ; 
 void* sbridge_get_tolm ; 
 void* sbridge_get_width ; 
 void* sbridge_interleave_list ; 
 void* sbridge_interleave_pkg ; 
 int sbridge_mci_bind_devs (struct mem_ctl_info*,struct sbridge_dev*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sbridge_register_mci(struct sbridge_dev *sbridge_dev, enum type type)
{
	struct mem_ctl_info *mci;
	struct edac_mc_layer layers[2];
	struct sbridge_pvt *pvt;
	struct pci_dev *pdev = sbridge_dev->pdev[0];
	int rc;

	/* allocate a new MC control structure */
	layers[0].type = EDAC_MC_LAYER_CHANNEL;
	layers[0].size = type == KNIGHTS_LANDING ?
		KNL_MAX_CHANNELS : NUM_CHANNELS;
	layers[0].is_virt_csrow = false;
	layers[1].type = EDAC_MC_LAYER_SLOT;
	layers[1].size = type == KNIGHTS_LANDING ? 1 : MAX_DIMMS;
	layers[1].is_virt_csrow = true;
	mci = edac_mc_alloc(sbridge_dev->mc, ARRAY_SIZE(layers), layers,
			    sizeof(*pvt));

	if (unlikely(!mci))
		return -ENOMEM;

	edac_dbg(0, "MC: mci = %p, dev = %p\n",
		 mci, &pdev->dev);

	pvt = mci->pvt_info;
	memset(pvt, 0, sizeof(*pvt));

	/* Associate sbridge_dev and mci for future usage */
	pvt->sbridge_dev = sbridge_dev;
	sbridge_dev->mci = mci;

	mci->mtype_cap = type == KNIGHTS_LANDING ?
		MEM_FLAG_DDR4 : MEM_FLAG_DDR3;
	mci->edac_ctl_cap = EDAC_FLAG_NONE;
	mci->edac_cap = EDAC_FLAG_NONE;
	mci->mod_name = EDAC_MOD_STR;
	mci->dev_name = pci_name(pdev);
	mci->ctl_page_to_phys = NULL;

	pvt->info.type = type;
	switch (type) {
	case IVY_BRIDGE:
		pvt->info.rankcfgr = IB_RANK_CFG_A;
		pvt->info.get_tolm = ibridge_get_tolm;
		pvt->info.get_tohm = ibridge_get_tohm;
		pvt->info.dram_rule = ibridge_dram_rule;
		pvt->info.get_memory_type = get_memory_type;
		pvt->info.get_node_id = get_node_id;
		pvt->info.get_ha = ibridge_get_ha;
		pvt->info.rir_limit = rir_limit;
		pvt->info.sad_limit = sad_limit;
		pvt->info.interleave_mode = interleave_mode;
		pvt->info.dram_attr = dram_attr;
		pvt->info.max_sad = ARRAY_SIZE(ibridge_dram_rule);
		pvt->info.interleave_list = ibridge_interleave_list;
		pvt->info.interleave_pkg = ibridge_interleave_pkg;
		pvt->info.get_width = ibridge_get_width;

		/* Store pci devices at mci for faster access */
		rc = ibridge_mci_bind_devs(mci, sbridge_dev);
		if (unlikely(rc < 0))
			goto fail0;
		get_source_id(mci);
		mci->ctl_name = kasprintf(GFP_KERNEL, "Ivy Bridge SrcID#%d_Ha#%d",
			pvt->sbridge_dev->source_id, pvt->sbridge_dev->dom);
		break;
	case SANDY_BRIDGE:
		pvt->info.rankcfgr = SB_RANK_CFG_A;
		pvt->info.get_tolm = sbridge_get_tolm;
		pvt->info.get_tohm = sbridge_get_tohm;
		pvt->info.dram_rule = sbridge_dram_rule;
		pvt->info.get_memory_type = get_memory_type;
		pvt->info.get_node_id = get_node_id;
		pvt->info.get_ha = sbridge_get_ha;
		pvt->info.rir_limit = rir_limit;
		pvt->info.sad_limit = sad_limit;
		pvt->info.interleave_mode = interleave_mode;
		pvt->info.dram_attr = dram_attr;
		pvt->info.max_sad = ARRAY_SIZE(sbridge_dram_rule);
		pvt->info.interleave_list = sbridge_interleave_list;
		pvt->info.interleave_pkg = sbridge_interleave_pkg;
		pvt->info.get_width = sbridge_get_width;

		/* Store pci devices at mci for faster access */
		rc = sbridge_mci_bind_devs(mci, sbridge_dev);
		if (unlikely(rc < 0))
			goto fail0;
		get_source_id(mci);
		mci->ctl_name = kasprintf(GFP_KERNEL, "Sandy Bridge SrcID#%d_Ha#%d",
			pvt->sbridge_dev->source_id, pvt->sbridge_dev->dom);
		break;
	case HASWELL:
		/* rankcfgr isn't used */
		pvt->info.get_tolm = haswell_get_tolm;
		pvt->info.get_tohm = haswell_get_tohm;
		pvt->info.dram_rule = ibridge_dram_rule;
		pvt->info.get_memory_type = haswell_get_memory_type;
		pvt->info.get_node_id = haswell_get_node_id;
		pvt->info.get_ha = ibridge_get_ha;
		pvt->info.rir_limit = haswell_rir_limit;
		pvt->info.sad_limit = sad_limit;
		pvt->info.interleave_mode = interleave_mode;
		pvt->info.dram_attr = dram_attr;
		pvt->info.max_sad = ARRAY_SIZE(ibridge_dram_rule);
		pvt->info.interleave_list = ibridge_interleave_list;
		pvt->info.interleave_pkg = ibridge_interleave_pkg;
		pvt->info.get_width = ibridge_get_width;

		/* Store pci devices at mci for faster access */
		rc = haswell_mci_bind_devs(mci, sbridge_dev);
		if (unlikely(rc < 0))
			goto fail0;
		get_source_id(mci);
		mci->ctl_name = kasprintf(GFP_KERNEL, "Haswell SrcID#%d_Ha#%d",
			pvt->sbridge_dev->source_id, pvt->sbridge_dev->dom);
		break;
	case BROADWELL:
		/* rankcfgr isn't used */
		pvt->info.get_tolm = haswell_get_tolm;
		pvt->info.get_tohm = haswell_get_tohm;
		pvt->info.dram_rule = ibridge_dram_rule;
		pvt->info.get_memory_type = haswell_get_memory_type;
		pvt->info.get_node_id = haswell_get_node_id;
		pvt->info.get_ha = ibridge_get_ha;
		pvt->info.rir_limit = haswell_rir_limit;
		pvt->info.sad_limit = sad_limit;
		pvt->info.interleave_mode = interleave_mode;
		pvt->info.dram_attr = dram_attr;
		pvt->info.max_sad = ARRAY_SIZE(ibridge_dram_rule);
		pvt->info.interleave_list = ibridge_interleave_list;
		pvt->info.interleave_pkg = ibridge_interleave_pkg;
		pvt->info.get_width = broadwell_get_width;

		/* Store pci devices at mci for faster access */
		rc = broadwell_mci_bind_devs(mci, sbridge_dev);
		if (unlikely(rc < 0))
			goto fail0;
		get_source_id(mci);
		mci->ctl_name = kasprintf(GFP_KERNEL, "Broadwell SrcID#%d_Ha#%d",
			pvt->sbridge_dev->source_id, pvt->sbridge_dev->dom);
		break;
	case KNIGHTS_LANDING:
		/* pvt->info.rankcfgr == ??? */
		pvt->info.get_tolm = knl_get_tolm;
		pvt->info.get_tohm = knl_get_tohm;
		pvt->info.dram_rule = knl_dram_rule;
		pvt->info.get_memory_type = knl_get_memory_type;
		pvt->info.get_node_id = knl_get_node_id;
		pvt->info.get_ha = knl_get_ha;
		pvt->info.rir_limit = NULL;
		pvt->info.sad_limit = knl_sad_limit;
		pvt->info.interleave_mode = knl_interleave_mode;
		pvt->info.dram_attr = dram_attr_knl;
		pvt->info.max_sad = ARRAY_SIZE(knl_dram_rule);
		pvt->info.interleave_list = knl_interleave_list;
		pvt->info.interleave_pkg = ibridge_interleave_pkg;
		pvt->info.get_width = knl_get_width;

		rc = knl_mci_bind_devs(mci, sbridge_dev);
		if (unlikely(rc < 0))
			goto fail0;
		get_source_id(mci);
		mci->ctl_name = kasprintf(GFP_KERNEL, "Knights Landing SrcID#%d_Ha#%d",
			pvt->sbridge_dev->source_id, pvt->sbridge_dev->dom);
		break;
	}

	if (!mci->ctl_name) {
		rc = -ENOMEM;
		goto fail0;
	}

	/* Get dimm basic config and the memory layout */
	rc = get_dimm_config(mci);
	if (rc < 0) {
		edac_dbg(0, "MC: failed to get_dimm_config()\n");
		goto fail;
	}
	get_memory_layout(mci);

	/* record ptr to the generic device */
	mci->pdev = &pdev->dev;

	/* add this new MC control structure to EDAC's list of MCs */
	if (unlikely(edac_mc_add_mc(mci))) {
		edac_dbg(0, "MC: failed edac_mc_add_mc()\n");
		rc = -EINVAL;
		goto fail;
	}

	return 0;

fail:
	kfree(mci->ctl_name);
fail0:
	edac_mc_free(mci);
	sbridge_dev->mci = NULL;
	return rc;
}