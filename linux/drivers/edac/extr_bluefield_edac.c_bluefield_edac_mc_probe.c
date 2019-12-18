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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct mem_ctl_info {int mtype_cap; char* ctl_name; int /*<<< orphan*/  edac_check; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  mod_name; int /*<<< orphan*/  edac_ctl_cap; struct device* pdev; struct bluefield_edac_priv* pvt_info; } ;
struct edac_mc_layer {unsigned int size; int is_virt_csrow; int /*<<< orphan*/  type; } ;
struct bluefield_edac_priv {unsigned int dimm_per_mc; int /*<<< orphan*/  emi_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct edac_mc_layer*) ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  EDAC_FLAG_SECDED ; 
 int /*<<< orphan*/  EDAC_MC_LAYER_SLOT ; 
 int /*<<< orphan*/  EDAC_OPSTATE_POLL ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MEM_FLAG_DDR4 ; 
 int MEM_FLAG_LRDDR4 ; 
 int MEM_FLAG_NVDIMM ; 
 int MEM_FLAG_RDDR4 ; 
 unsigned int MLXBF_EDAC_MAX_DIMM_PER_MC ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bluefield_edac_check ; 
 int /*<<< orphan*/  bluefield_edac_init_dimms (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 scalar_t__ device_property_read_u32 (struct device*,char*,unsigned int*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 int edac_mc_add_mc (struct mem_ctl_info*) ; 
 struct mem_ctl_info* edac_mc_alloc (unsigned int,int /*<<< orphan*/ ,struct edac_mc_layer*,int) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  edac_op_state ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mem_ctl_info*) ; 

__attribute__((used)) static int bluefield_edac_mc_probe(struct platform_device *pdev)
{
	struct bluefield_edac_priv *priv;
	struct device *dev = &pdev->dev;
	struct edac_mc_layer layers[1];
	struct mem_ctl_info *mci;
	struct resource *emi_res;
	unsigned int mc_idx, dimm_count;
	int rc, ret;

	/* Read the MSS (Memory SubSystem) index from ACPI table. */
	if (device_property_read_u32(dev, "mss_number", &mc_idx)) {
		dev_warn(dev, "bf_edac: MSS number unknown\n");
		return -EINVAL;
	}

	/* Read the DIMMs per MC from ACPI table. */
	if (device_property_read_u32(dev, "dimm_per_mc", &dimm_count)) {
		dev_warn(dev, "bf_edac: DIMMs per MC unknown\n");
		return -EINVAL;
	}

	if (dimm_count > MLXBF_EDAC_MAX_DIMM_PER_MC) {
		dev_warn(dev, "bf_edac: DIMMs per MC not valid\n");
		return -EINVAL;
	}

	emi_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!emi_res)
		return -EINVAL;

	layers[0].type = EDAC_MC_LAYER_SLOT;
	layers[0].size = dimm_count;
	layers[0].is_virt_csrow = true;

	mci = edac_mc_alloc(mc_idx, ARRAY_SIZE(layers), layers, sizeof(*priv));
	if (!mci)
		return -ENOMEM;

	priv = mci->pvt_info;

	priv->dimm_per_mc = dimm_count;
	priv->emi_base = devm_ioremap_resource(dev, emi_res);
	if (IS_ERR(priv->emi_base)) {
		dev_err(dev, "failed to map EMI IO resource\n");
		ret = PTR_ERR(priv->emi_base);
		goto err;
	}

	mci->pdev = dev;
	mci->mtype_cap = MEM_FLAG_DDR4 | MEM_FLAG_RDDR4 |
			 MEM_FLAG_LRDDR4 | MEM_FLAG_NVDIMM;
	mci->edac_ctl_cap = EDAC_FLAG_SECDED;

	mci->mod_name = DRIVER_NAME;
	mci->ctl_name = "BlueField_Memory_Controller";
	mci->dev_name = dev_name(dev);
	mci->edac_check = bluefield_edac_check;

	/* Initialize mci with the actual populated DIMM information. */
	bluefield_edac_init_dimms(mci);

	platform_set_drvdata(pdev, mci);

	/* Register with EDAC core */
	rc = edac_mc_add_mc(mci);
	if (rc) {
		dev_err(dev, "failed to register with EDAC core\n");
		ret = rc;
		goto err;
	}

	/* Only POLL mode supported so far. */
	edac_op_state = EDAC_OPSTATE_POLL;

	return 0;

err:
	edac_mc_free(mci);

	return ret;

}