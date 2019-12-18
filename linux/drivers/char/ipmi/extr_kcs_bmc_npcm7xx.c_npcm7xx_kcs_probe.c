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
typedef  int u32 ;
struct device {TYPE_1__* parent; int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct npcm7xx_kcs_bmc {TYPE_3__* reg; int /*<<< orphan*/  map; } ;
struct TYPE_5__ {int /*<<< orphan*/  str; int /*<<< orphan*/  odr; int /*<<< orphan*/  idr; } ;
struct kcs_bmc {TYPE_2__ ioreg; int /*<<< orphan*/  miscdev; int /*<<< orphan*/  io_outputb; int /*<<< orphan*/  io_inputb; } ;
struct TYPE_6__ {int /*<<< orphan*/  sts; int /*<<< orphan*/  dob; int /*<<< orphan*/  dib; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int KCS_CHANNEL_MAX ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct kcs_bmc*) ; 
 struct kcs_bmc* kcs_bmc_alloc (struct device*,int,int) ; 
 struct npcm7xx_kcs_bmc* kcs_bmc_priv (struct kcs_bmc*) ; 
 int misc_register (int /*<<< orphan*/ *) ; 
 int npcm7xx_kcs_config_irq (struct kcs_bmc*,struct platform_device*) ; 
 int /*<<< orphan*/  npcm7xx_kcs_enable_channel (struct kcs_bmc*,int) ; 
 int /*<<< orphan*/  npcm7xx_kcs_inb ; 
 int /*<<< orphan*/  npcm7xx_kcs_outb ; 
 TYPE_3__* npcm7xx_kcs_reg_tbl ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  pr_info (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int npcm7xx_kcs_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct npcm7xx_kcs_bmc *priv;
	struct kcs_bmc *kcs_bmc;
	u32 chan;
	int rc;

	rc = of_property_read_u32(dev->of_node, "kcs_chan", &chan);
	if (rc != 0 || chan == 0 || chan > KCS_CHANNEL_MAX) {
		dev_err(dev, "no valid 'kcs_chan' configured\n");
		return -ENODEV;
	}

	kcs_bmc = kcs_bmc_alloc(dev, sizeof(*priv), chan);
	if (!kcs_bmc)
		return -ENOMEM;

	priv = kcs_bmc_priv(kcs_bmc);
	priv->map = syscon_node_to_regmap(dev->parent->of_node);
	if (IS_ERR(priv->map)) {
		dev_err(dev, "Couldn't get regmap\n");
		return -ENODEV;
	}
	priv->reg = &npcm7xx_kcs_reg_tbl[chan - 1];

	kcs_bmc->ioreg.idr = priv->reg->dib;
	kcs_bmc->ioreg.odr = priv->reg->dob;
	kcs_bmc->ioreg.str = priv->reg->sts;
	kcs_bmc->io_inputb = npcm7xx_kcs_inb;
	kcs_bmc->io_outputb = npcm7xx_kcs_outb;

	dev_set_drvdata(dev, kcs_bmc);

	npcm7xx_kcs_enable_channel(kcs_bmc, true);
	rc = npcm7xx_kcs_config_irq(kcs_bmc, pdev);
	if (rc)
		return rc;

	rc = misc_register(&kcs_bmc->miscdev);
	if (rc) {
		dev_err(dev, "Unable to register device\n");
		return rc;
	}

	pr_info("channel=%u idr=0x%x odr=0x%x str=0x%x\n",
		chan,
		kcs_bmc->ioreg.idr, kcs_bmc->ioreg.odr, kcs_bmc->ioreg.str);

	return 0;
}