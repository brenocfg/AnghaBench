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
typedef  int /*<<< orphan*/  tmp_ctx ;
struct xgene_edac_mc_ctx {char* name; int /*<<< orphan*/  next; struct mem_ctl_info* mci; int /*<<< orphan*/  mcu_id; int /*<<< orphan*/  mcu_csr; struct xgene_edac* edac; } ;
struct xgene_edac {int /*<<< orphan*/  dev; int /*<<< orphan*/  mcus; } ;
struct resource {int dummy; } ;
struct mem_ctl_info {char* ctl_name; char* dev_name; int mtype_cap; int /*<<< orphan*/  edac_check; int /*<<< orphan*/  scrub_mode; int /*<<< orphan*/  scrub_cap; int /*<<< orphan*/ * ctl_page_to_phys; int /*<<< orphan*/  mod_name; void* edac_cap; void* edac_ctl_cap; int /*<<< orphan*/  dev; int /*<<< orphan*/ * pdev; struct xgene_edac_mc_ctx* pvt_info; } ;
struct edac_mc_layer {int size; int is_virt_csrow; int /*<<< orphan*/  type; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct edac_mc_layer*) ; 
 void* EDAC_FLAG_SECDED ; 
 int /*<<< orphan*/  EDAC_MC_LAYER_CHANNEL ; 
 int /*<<< orphan*/  EDAC_MC_LAYER_CHIP_SELECT ; 
 int /*<<< orphan*/  EDAC_MOD_STR ; 
 scalar_t__ EDAC_OPSTATE_POLL ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MEM_FLAG_DDR ; 
 int MEM_FLAG_DDR2 ; 
 int MEM_FLAG_DDR3 ; 
 int MEM_FLAG_RDDR ; 
 int MEM_FLAG_RDDR2 ; 
 int MEM_FLAG_RDDR3 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCRUB_FLAG_HW_SRC ; 
 int /*<<< orphan*/  SCRUB_HW_SRC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ ,struct resource*) ; 
 int /*<<< orphan*/  devres_open_group (int /*<<< orphan*/ ,int (*) (struct xgene_edac*,struct device_node*),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_release_group (int /*<<< orphan*/ ,int (*) (struct xgene_edac*,struct device_node*)) ; 
 int /*<<< orphan*/  devres_remove_group (int /*<<< orphan*/ ,int (*) (struct xgene_edac*,struct device_node*)) ; 
 scalar_t__ edac_mc_add_mc (struct mem_ctl_info*) ; 
 struct mem_ctl_info* edac_mc_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct edac_mc_layer*,int) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 scalar_t__ edac_op_state ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct xgene_edac_mc_ctx*,int /*<<< orphan*/ ,int) ; 
 int of_address_to_resource (struct device_node*,int /*<<< orphan*/ ,struct resource*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgene_edac_mc_check ; 
 int /*<<< orphan*/  xgene_edac_mc_create_debugfs_node (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  xgene_edac_mc_irq_ctl (struct mem_ctl_info*,int) ; 
 int /*<<< orphan*/  xgene_edac_mc_is_active (struct xgene_edac_mc_ctx*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgene_edac_mc_add(struct xgene_edac *edac, struct device_node *np)
{
	struct mem_ctl_info *mci;
	struct edac_mc_layer layers[2];
	struct xgene_edac_mc_ctx tmp_ctx;
	struct xgene_edac_mc_ctx *ctx;
	struct resource res;
	int rc;

	memset(&tmp_ctx, 0, sizeof(tmp_ctx));
	tmp_ctx.edac = edac;

	if (!devres_open_group(edac->dev, xgene_edac_mc_add, GFP_KERNEL))
		return -ENOMEM;

	rc = of_address_to_resource(np, 0, &res);
	if (rc < 0) {
		dev_err(edac->dev, "no MCU resource address\n");
		goto err_group;
	}
	tmp_ctx.mcu_csr = devm_ioremap_resource(edac->dev, &res);
	if (IS_ERR(tmp_ctx.mcu_csr)) {
		dev_err(edac->dev, "unable to map MCU resource\n");
		rc = PTR_ERR(tmp_ctx.mcu_csr);
		goto err_group;
	}

	/* Ignore non-active MCU */
	if (of_property_read_u32(np, "memory-controller", &tmp_ctx.mcu_id)) {
		dev_err(edac->dev, "no memory-controller property\n");
		rc = -ENODEV;
		goto err_group;
	}
	if (!xgene_edac_mc_is_active(&tmp_ctx, tmp_ctx.mcu_id)) {
		rc = -ENODEV;
		goto err_group;
	}

	layers[0].type = EDAC_MC_LAYER_CHIP_SELECT;
	layers[0].size = 4;
	layers[0].is_virt_csrow = true;
	layers[1].type = EDAC_MC_LAYER_CHANNEL;
	layers[1].size = 2;
	layers[1].is_virt_csrow = false;
	mci = edac_mc_alloc(tmp_ctx.mcu_id, ARRAY_SIZE(layers), layers,
			    sizeof(*ctx));
	if (!mci) {
		rc = -ENOMEM;
		goto err_group;
	}

	ctx = mci->pvt_info;
	*ctx = tmp_ctx;		/* Copy over resource value */
	ctx->name = "xgene_edac_mc_err";
	ctx->mci = mci;
	mci->pdev = &mci->dev;
	mci->ctl_name = ctx->name;
	mci->dev_name = ctx->name;

	mci->mtype_cap = MEM_FLAG_RDDR | MEM_FLAG_RDDR2 | MEM_FLAG_RDDR3 |
			 MEM_FLAG_DDR | MEM_FLAG_DDR2 | MEM_FLAG_DDR3;
	mci->edac_ctl_cap = EDAC_FLAG_SECDED;
	mci->edac_cap = EDAC_FLAG_SECDED;
	mci->mod_name = EDAC_MOD_STR;
	mci->ctl_page_to_phys = NULL;
	mci->scrub_cap = SCRUB_FLAG_HW_SRC;
	mci->scrub_mode = SCRUB_HW_SRC;

	if (edac_op_state == EDAC_OPSTATE_POLL)
		mci->edac_check = xgene_edac_mc_check;

	if (edac_mc_add_mc(mci)) {
		dev_err(edac->dev, "edac_mc_add_mc failed\n");
		rc = -EINVAL;
		goto err_free;
	}

	xgene_edac_mc_create_debugfs_node(mci);

	list_add(&ctx->next, &edac->mcus);

	xgene_edac_mc_irq_ctl(mci, true);

	devres_remove_group(edac->dev, xgene_edac_mc_add);

	dev_info(edac->dev, "X-Gene EDAC MC registered\n");
	return 0;

err_free:
	edac_mc_free(mci);
err_group:
	devres_release_group(edac->dev, xgene_edac_mc_add);
	return rc;
}