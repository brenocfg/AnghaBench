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
typedef  int /*<<< orphan*/  u32 ;
struct fpga_manager {struct a10_fpga_priv* priv; } ;
struct a10_fpga_priv {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  A10_FPGAMGR_IMGCFG_CTL_02_CDRATIO_MASK ; 
 unsigned int A10_FPGAMGR_IMGCFG_CTL_02_CDRATIO_SHIFT ; 
 int /*<<< orphan*/  A10_FPGAMGR_IMGCFG_CTL_02_OFST ; 
 int EINVAL ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int socfpga_a10_fpga_compressed (int /*<<< orphan*/ *,size_t) ; 
 int socfpga_a10_fpga_encrypted (int /*<<< orphan*/ *,size_t) ; 
 unsigned int socfpga_a10_fpga_get_cd_ratio (unsigned int,int,int) ; 

__attribute__((used)) static int socfpga_a10_fpga_set_cdratio(struct fpga_manager *mgr,
					unsigned int cfg_width,
					const char *buf, size_t count)
{
	struct a10_fpga_priv *priv = mgr->priv;
	unsigned int cd_ratio;
	int encrypt, compress;

	encrypt = socfpga_a10_fpga_encrypted((u32 *)buf, count / 4);
	if (encrypt < 0)
		return -EINVAL;

	compress = socfpga_a10_fpga_compressed((u32 *)buf, count / 4);
	if (compress < 0)
		return -EINVAL;

	cd_ratio = socfpga_a10_fpga_get_cd_ratio(cfg_width, encrypt, compress);

	regmap_update_bits(priv->regmap, A10_FPGAMGR_IMGCFG_CTL_02_OFST,
			   A10_FPGAMGR_IMGCFG_CTL_02_CDRATIO_MASK,
			   cd_ratio << A10_FPGAMGR_IMGCFG_CTL_02_CDRATIO_SHIFT);

	return 0;
}