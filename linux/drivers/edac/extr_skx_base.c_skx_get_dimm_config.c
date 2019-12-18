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
typedef  int /*<<< orphan*/  u32 ;
struct skx_pvt {struct skx_imc* imc; } ;
struct skx_imc {int /*<<< orphan*/  mc; TYPE_1__* chan; } ;
struct mem_ctl_info {int /*<<< orphan*/  n_layers; int /*<<< orphan*/  dimms; int /*<<< orphan*/  layers; struct skx_pvt* pvt_info; } ;
struct dimm_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cdev; } ;

/* Variables and functions */
 struct dimm_info* EDAC_DIMM_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDAC_MOD_STR ; 
 int ENODEV ; 
 scalar_t__ IS_DIMM_PRESENT (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_NVDIMM_PRESENT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int SKX_NUM_CHANNELS ; 
 int SKX_NUM_DIMMS ; 
 int /*<<< orphan*/  nvdimm_count ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skx_check_ecc (int /*<<< orphan*/ ) ; 
 scalar_t__ skx_get_dimm_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dimm_info*,struct skx_imc*,int,int) ; 
 scalar_t__ skx_get_nvdimm_info (struct dimm_info*,struct skx_imc*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skx_printk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skx_get_dimm_config(struct mem_ctl_info *mci)
{
	struct skx_pvt *pvt = mci->pvt_info;
	struct skx_imc *imc = pvt->imc;
	u32 mtr, amap, mcddrtcfg;
	struct dimm_info *dimm;
	int i, j;
	int ndimms;

	for (i = 0; i < SKX_NUM_CHANNELS; i++) {
		ndimms = 0;
		pci_read_config_dword(imc->chan[i].cdev, 0x8C, &amap);
		pci_read_config_dword(imc->chan[i].cdev, 0x400, &mcddrtcfg);
		for (j = 0; j < SKX_NUM_DIMMS; j++) {
			dimm = EDAC_DIMM_PTR(mci->layers, mci->dimms,
					     mci->n_layers, i, j, 0);
			pci_read_config_dword(imc->chan[i].cdev,
					      0x80 + 4 * j, &mtr);
			if (IS_DIMM_PRESENT(mtr)) {
				ndimms += skx_get_dimm_info(mtr, amap, dimm, imc, i, j);
			} else if (IS_NVDIMM_PRESENT(mcddrtcfg, j)) {
				ndimms += skx_get_nvdimm_info(dimm, imc, i, j,
							      EDAC_MOD_STR);
				nvdimm_count++;
			}
		}
		if (ndimms && !skx_check_ecc(imc->chan[0].cdev)) {
			skx_printk(KERN_ERR, "ECC is disabled on imc %d\n", imc->mc);
			return -ENODEV;
		}
	}

	return 0;
}