#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct imx_ahci_priv {scalar_t__ type; } ;
struct ata_port {int /*<<< orphan*/  dev; } ;
struct ata_link {struct ata_port* ap; } ;
struct ata_host {struct ahci_host_priv* private_data; } ;
struct ahci_host_priv {struct imx_ahci_priv* plat_data; } ;
struct TYPE_4__ {int (* softreset ) (struct ata_link*,unsigned int*,unsigned long) ;} ;
struct TYPE_3__ {int (* softreset ) (struct ata_link*,unsigned int*,unsigned long) ;} ;

/* Variables and functions */
 scalar_t__ AHCI_IMX53 ; 
 int EIO ; 
 TYPE_2__ ahci_ops ; 
 TYPE_1__ ahci_pmp_retry_srst_ops ; 
 struct ata_host* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int stub1 (struct ata_link*,unsigned int*,unsigned long) ; 
 int stub2 (struct ata_link*,unsigned int*,unsigned long) ; 

__attribute__((used)) static int ahci_imx_softreset(struct ata_link *link, unsigned int *class,
		       unsigned long deadline)
{
	struct ata_port *ap = link->ap;
	struct ata_host *host = dev_get_drvdata(ap->dev);
	struct ahci_host_priv *hpriv = host->private_data;
	struct imx_ahci_priv *imxpriv = hpriv->plat_data;
	int ret = -EIO;

	if (imxpriv->type == AHCI_IMX53)
		ret = ahci_pmp_retry_srst_ops.softreset(link, class, deadline);
	else
		ret = ahci_ops.softreset(link, class, deadline);

	return ret;
}