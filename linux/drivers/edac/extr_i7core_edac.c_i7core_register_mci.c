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
struct mem_ctl_info {char* mod_name; int /*<<< orphan*/  ctl_name; int /*<<< orphan*/ * pdev; int /*<<< orphan*/ * ctl_page_to_phys; int /*<<< orphan*/  dev_name; void* edac_cap; void* edac_ctl_cap; int /*<<< orphan*/  mtype_cap; struct i7core_pvt* pvt_info; } ;
struct TYPE_3__ {int dimm; int rank; int bank; int page; int col; scalar_t__ channel; } ;
struct i7core_pvt {int /*<<< orphan*/  dclk_freq; TYPE_1__ inject; scalar_t__ enable_scrub; struct i7core_dev* i7core_dev; } ;
struct i7core_dev {struct mem_ctl_info* mci; TYPE_2__** pdev; int /*<<< orphan*/  socket; } ;
struct edac_mc_layer {int is_virt_csrow; int /*<<< orphan*/  size; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct edac_mc_layer*) ; 
 void* EDAC_FLAG_NONE ; 
 int /*<<< orphan*/  EDAC_MC_LAYER_CHANNEL ; 
 int /*<<< orphan*/  EDAC_MC_LAYER_SLOT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAX_DIMMS ; 
 int /*<<< orphan*/  MEM_FLAG_DDR3 ; 
 int /*<<< orphan*/  NUM_CHANS ; 
 int /*<<< orphan*/  edac_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int edac_mc_add_mc_with_groups (struct mem_ctl_info*,int /*<<< orphan*/ ) ; 
 struct mem_ctl_info* edac_mc_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct edac_mc_layer*,int) ; 
 int /*<<< orphan*/  edac_mc_del_mc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  enable_sdram_scrub_setting (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  get_dclk_freq () ; 
 int /*<<< orphan*/  get_dimm_config (struct mem_ctl_info*) ; 
 scalar_t__ i7core_create_sysfs_devices (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  i7core_dev_groups ; 
 int /*<<< orphan*/  i7core_pci_ctl_create (struct i7core_pvt*) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int mci_bind_devs (struct mem_ctl_info*,struct i7core_dev*) ; 
 int /*<<< orphan*/  memset (struct i7core_pvt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_name (TYPE_2__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int i7core_register_mci(struct i7core_dev *i7core_dev)
{
	struct mem_ctl_info *mci;
	struct i7core_pvt *pvt;
	int rc;
	struct edac_mc_layer layers[2];

	/* allocate a new MC control structure */

	layers[0].type = EDAC_MC_LAYER_CHANNEL;
	layers[0].size = NUM_CHANS;
	layers[0].is_virt_csrow = false;
	layers[1].type = EDAC_MC_LAYER_SLOT;
	layers[1].size = MAX_DIMMS;
	layers[1].is_virt_csrow = true;
	mci = edac_mc_alloc(i7core_dev->socket, ARRAY_SIZE(layers), layers,
			    sizeof(*pvt));
	if (unlikely(!mci))
		return -ENOMEM;

	edac_dbg(0, "MC: mci = %p, dev = %p\n", mci, &i7core_dev->pdev[0]->dev);

	pvt = mci->pvt_info;
	memset(pvt, 0, sizeof(*pvt));

	/* Associates i7core_dev and mci for future usage */
	pvt->i7core_dev = i7core_dev;
	i7core_dev->mci = mci;

	/*
	 * FIXME: how to handle RDDR3 at MCI level? It is possible to have
	 * Mixed RDDR3/UDDR3 with Nehalem, provided that they are on different
	 * memory channels
	 */
	mci->mtype_cap = MEM_FLAG_DDR3;
	mci->edac_ctl_cap = EDAC_FLAG_NONE;
	mci->edac_cap = EDAC_FLAG_NONE;
	mci->mod_name = "i7core_edac.c";

	mci->ctl_name = kasprintf(GFP_KERNEL, "i7 core #%d", i7core_dev->socket);
	if (!mci->ctl_name) {
		rc = -ENOMEM;
		goto fail1;
	}

	mci->dev_name = pci_name(i7core_dev->pdev[0]);
	mci->ctl_page_to_phys = NULL;

	/* Store pci devices at mci for faster access */
	rc = mci_bind_devs(mci, i7core_dev);
	if (unlikely(rc < 0))
		goto fail0;


	/* Get dimm basic config */
	get_dimm_config(mci);
	/* record ptr to the generic device */
	mci->pdev = &i7core_dev->pdev[0]->dev;

	/* Enable scrubrate setting */
	if (pvt->enable_scrub)
		enable_sdram_scrub_setting(mci);

	/* add this new MC control structure to EDAC's list of MCs */
	if (unlikely(edac_mc_add_mc_with_groups(mci, i7core_dev_groups))) {
		edac_dbg(0, "MC: failed edac_mc_add_mc()\n");
		/* FIXME: perhaps some code should go here that disables error
		 * reporting if we just enabled it
		 */

		rc = -EINVAL;
		goto fail0;
	}
	if (i7core_create_sysfs_devices(mci)) {
		edac_dbg(0, "MC: failed to create sysfs nodes\n");
		edac_mc_del_mc(mci->pdev);
		rc = -EINVAL;
		goto fail0;
	}

	/* Default error mask is any memory */
	pvt->inject.channel = 0;
	pvt->inject.dimm = -1;
	pvt->inject.rank = -1;
	pvt->inject.bank = -1;
	pvt->inject.page = -1;
	pvt->inject.col = -1;

	/* allocating generic PCI control info */
	i7core_pci_ctl_create(pvt);

	/* DCLK for scrub rate setting */
	pvt->dclk_freq = get_dclk_freq();

	return 0;

fail0:
	kfree(mci->ctl_name);

fail1:
	edac_mc_free(mci);
	i7core_dev->mci = NULL;
	return rc;
}