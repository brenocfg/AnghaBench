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
struct fpga_manager {struct fpga_compat_id* compat_id; } ;
struct fpga_compat_id {int dummy; } ;
struct fme_mgr_priv {scalar_t__ ioaddr; } ;
struct dfl_fme_mgr_pdata {scalar_t__ ioaddr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 struct dfl_fme_mgr_pdata* dev_get_platdata (struct device*) ; 
 struct fpga_manager* devm_fpga_mgr_create (struct device*,char*,int /*<<< orphan*/ *,struct fme_mgr_priv*) ; 
 scalar_t__ devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fme_mgr_get_compat_id (scalar_t__,struct fpga_compat_id*) ; 
 int /*<<< orphan*/  fme_mgr_ops ; 
 int fpga_mgr_register (struct fpga_manager*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fpga_manager*) ; 

__attribute__((used)) static int fme_mgr_probe(struct platform_device *pdev)
{
	struct dfl_fme_mgr_pdata *pdata = dev_get_platdata(&pdev->dev);
	struct fpga_compat_id *compat_id;
	struct device *dev = &pdev->dev;
	struct fme_mgr_priv *priv;
	struct fpga_manager *mgr;
	struct resource *res;

	priv = devm_kzalloc(dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	if (pdata->ioaddr)
		priv->ioaddr = pdata->ioaddr;

	if (!priv->ioaddr) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
		priv->ioaddr = devm_ioremap_resource(dev, res);
		if (IS_ERR(priv->ioaddr))
			return PTR_ERR(priv->ioaddr);
	}

	compat_id = devm_kzalloc(dev, sizeof(*compat_id), GFP_KERNEL);
	if (!compat_id)
		return -ENOMEM;

	fme_mgr_get_compat_id(priv->ioaddr, compat_id);

	mgr = devm_fpga_mgr_create(dev, "DFL FME FPGA Manager",
				   &fme_mgr_ops, priv);
	if (!mgr)
		return -ENOMEM;

	mgr->compat_id = compat_id;
	platform_set_drvdata(pdev, mgr);

	return fpga_mgr_register(mgr);
}