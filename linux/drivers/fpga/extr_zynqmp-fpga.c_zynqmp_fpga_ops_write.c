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
struct zynqmp_fpga_priv {int flags; int /*<<< orphan*/  dev; } ;
struct zynqmp_eemi_ops {int (* fpga_load ) (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ;} ;
struct fpga_manager {struct zynqmp_fpga_priv* priv; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int FPGA_MGR_PARTIAL_RECONFIG ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (struct zynqmp_eemi_ops const*) ; 
 int /*<<< orphan*/  XILINX_ZYNQMP_PM_FPGA_PARTIAL ; 
 char* dma_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,size_t,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int stub1 (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 
 struct zynqmp_eemi_ops* zynqmp_pm_get_eemi_ops () ; 

__attribute__((used)) static int zynqmp_fpga_ops_write(struct fpga_manager *mgr,
				 const char *buf, size_t size)
{
	const struct zynqmp_eemi_ops *eemi_ops = zynqmp_pm_get_eemi_ops();
	struct zynqmp_fpga_priv *priv;
	dma_addr_t dma_addr;
	u32 eemi_flags = 0;
	char *kbuf;
	int ret;

	if (IS_ERR_OR_NULL(eemi_ops) || !eemi_ops->fpga_load)
		return -ENXIO;

	priv = mgr->priv;

	kbuf = dma_alloc_coherent(priv->dev, size, &dma_addr, GFP_KERNEL);
	if (!kbuf)
		return -ENOMEM;

	memcpy(kbuf, buf, size);

	wmb(); /* ensure all writes are done before initiate FW call */

	if (priv->flags & FPGA_MGR_PARTIAL_RECONFIG)
		eemi_flags |= XILINX_ZYNQMP_PM_FPGA_PARTIAL;

	ret = eemi_ops->fpga_load(dma_addr, size, eemi_flags);

	dma_free_coherent(priv->dev, size, kbuf, dma_addr);

	return ret;
}