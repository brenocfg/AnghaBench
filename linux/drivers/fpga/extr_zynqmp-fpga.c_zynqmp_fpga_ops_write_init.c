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
struct zynqmp_fpga_priv {int /*<<< orphan*/  flags; } ;
struct fpga_manager {struct zynqmp_fpga_priv* priv; } ;
struct fpga_image_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */

__attribute__((used)) static int zynqmp_fpga_ops_write_init(struct fpga_manager *mgr,
				      struct fpga_image_info *info,
				      const char *buf, size_t size)
{
	struct zynqmp_fpga_priv *priv;

	priv = mgr->priv;
	priv->flags = info->flags;

	return 0;
}