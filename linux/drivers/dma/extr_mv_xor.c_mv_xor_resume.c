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
struct platform_device {int dummy; } ;
struct mv_xor_device {scalar_t__ xor_type; struct mv_xor_chan** channels; } ;
struct mv_xor_chan {int /*<<< orphan*/  saved_int_mask_reg; int /*<<< orphan*/  saved_config_reg; } ;
struct mbus_dram_target_info {int dummy; } ;

/* Variables and functions */
 int MV_XOR_MAX_CHANNELS ; 
 scalar_t__ XOR_ARMADA_37XX ; 
 int /*<<< orphan*/  XOR_CONFIG (struct mv_xor_chan*) ; 
 int /*<<< orphan*/  XOR_INTR_MASK (struct mv_xor_chan*) ; 
 struct mbus_dram_target_info* mv_mbus_dram_info () ; 
 int /*<<< orphan*/  mv_xor_conf_mbus_windows (struct mv_xor_device*,struct mbus_dram_target_info const*) ; 
 int /*<<< orphan*/  mv_xor_conf_mbus_windows_a3700 (struct mv_xor_device*) ; 
 struct mv_xor_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv_xor_resume(struct platform_device *dev)
{
	struct mv_xor_device *xordev = platform_get_drvdata(dev);
	const struct mbus_dram_target_info *dram;
	int i;

	for (i = 0; i < MV_XOR_MAX_CHANNELS; i++) {
		struct mv_xor_chan *mv_chan = xordev->channels[i];

		if (!mv_chan)
			continue;

		writel_relaxed(mv_chan->saved_config_reg,
			       XOR_CONFIG(mv_chan));
		writel_relaxed(mv_chan->saved_int_mask_reg,
			       XOR_INTR_MASK(mv_chan));
	}

	if (xordev->xor_type == XOR_ARMADA_37XX) {
		mv_xor_conf_mbus_windows_a3700(xordev);
		return 0;
	}

	dram = mv_mbus_dram_info();
	if (dram)
		mv_xor_conf_mbus_windows(xordev, dram);

	return 0;
}