#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ intr_sec_ena; scalar_t__ intr_ded_ena; int /*<<< orphan*/  ecc_ena; } ;
union cvmx_lmcx_mem_cfg0 {void* u64; TYPE_1__ s; } ;
struct TYPE_6__ {scalar_t__ intr_sec_ena; scalar_t__ intr_ded_ena; } ;
union cvmx_lmcx_int_en {void* u64; TYPE_3__ s; } ;
struct TYPE_5__ {int /*<<< orphan*/  ecc_ena; } ;
union cvmx_lmcx_config {TYPE_2__ s; void* u64; } ;
struct platform_device {int id; int /*<<< orphan*/  dev; } ;
struct octeon_lmc_pvt {int dummy; } ;
struct mem_ctl_info {char* mod_name; char* ctl_name; int /*<<< orphan*/  edac_check; void* dev_name; int /*<<< orphan*/ * pdev; } ;
struct edac_mc_layer {int size; int is_virt_csrow; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct edac_mc_layer*) ; 
 int /*<<< orphan*/  CVMX_LMCX_CONFIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_LMCX_MEM_CFG0 (int) ; 
 int /*<<< orphan*/  EDAC_MC_LAYER_CHANNEL ; 
 int ENXIO ; 
 scalar_t__ OCTEON_IS_OCTEON1PLUS () ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 void* dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ edac_mc_add_mc_with_groups (struct mem_ctl_info*,int /*<<< orphan*/ ) ; 
 struct mem_ctl_info* edac_mc_alloc (int,int /*<<< orphan*/ ,struct edac_mc_layer*,int) ; 
 int /*<<< orphan*/  edac_mc_free (struct mem_ctl_info*) ; 
 int /*<<< orphan*/  octeon_dev_groups ; 
 int /*<<< orphan*/  octeon_lmc_edac_poll ; 
 int /*<<< orphan*/  octeon_lmc_edac_poll_o2 ; 
 int /*<<< orphan*/  opstate_init () ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mem_ctl_info*) ; 

__attribute__((used)) static int octeon_lmc_edac_probe(struct platform_device *pdev)
{
	struct mem_ctl_info *mci;
	struct edac_mc_layer layers[1];
	int mc = pdev->id;

	opstate_init();

	layers[0].type = EDAC_MC_LAYER_CHANNEL;
	layers[0].size = 1;
	layers[0].is_virt_csrow = false;

	if (OCTEON_IS_OCTEON1PLUS()) {
		union cvmx_lmcx_mem_cfg0 cfg0;

		cfg0.u64 = cvmx_read_csr(CVMX_LMCX_MEM_CFG0(0));
		if (!cfg0.s.ecc_ena) {
			dev_info(&pdev->dev, "Disabled (ECC not enabled)\n");
			return 0;
		}

		mci = edac_mc_alloc(mc, ARRAY_SIZE(layers), layers, sizeof(struct octeon_lmc_pvt));
		if (!mci)
			return -ENXIO;

		mci->pdev = &pdev->dev;
		mci->dev_name = dev_name(&pdev->dev);

		mci->mod_name = "octeon-lmc";
		mci->ctl_name = "octeon-lmc-err";
		mci->edac_check = octeon_lmc_edac_poll;

		if (edac_mc_add_mc_with_groups(mci, octeon_dev_groups)) {
			dev_err(&pdev->dev, "edac_mc_add_mc() failed\n");
			edac_mc_free(mci);
			return -ENXIO;
		}

		cfg0.u64 = cvmx_read_csr(CVMX_LMCX_MEM_CFG0(mc));
		cfg0.s.intr_ded_ena = 0;	/* We poll */
		cfg0.s.intr_sec_ena = 0;
		cvmx_write_csr(CVMX_LMCX_MEM_CFG0(mc), cfg0.u64);
	} else {
		/* OCTEON II */
		union cvmx_lmcx_int_en en;
		union cvmx_lmcx_config config;

		config.u64 = cvmx_read_csr(CVMX_LMCX_CONFIG(0));
		if (!config.s.ecc_ena) {
			dev_info(&pdev->dev, "Disabled (ECC not enabled)\n");
			return 0;
		}

		mci = edac_mc_alloc(mc, ARRAY_SIZE(layers), layers, sizeof(struct octeon_lmc_pvt));
		if (!mci)
			return -ENXIO;

		mci->pdev = &pdev->dev;
		mci->dev_name = dev_name(&pdev->dev);

		mci->mod_name = "octeon-lmc";
		mci->ctl_name = "co_lmc_err";
		mci->edac_check = octeon_lmc_edac_poll_o2;

		if (edac_mc_add_mc_with_groups(mci, octeon_dev_groups)) {
			dev_err(&pdev->dev, "edac_mc_add_mc() failed\n");
			edac_mc_free(mci);
			return -ENXIO;
		}

		en.u64 = cvmx_read_csr(CVMX_LMCX_MEM_CFG0(mc));
		en.s.intr_ded_ena = 0;	/* We poll */
		en.s.intr_sec_ena = 0;
		cvmx_write_csr(CVMX_LMCX_MEM_CFG0(mc), en.u64);
	}
	platform_set_drvdata(pdev, mci);

	return 0;
}