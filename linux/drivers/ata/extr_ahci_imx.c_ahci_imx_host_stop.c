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
struct imx_ahci_priv {int /*<<< orphan*/  sata_clk; } ;
struct ata_host {struct ahci_host_priv* private_data; } ;
struct ahci_host_priv {struct imx_ahci_priv* plat_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx_sata_disable (struct ahci_host_priv*) ; 

__attribute__((used)) static void ahci_imx_host_stop(struct ata_host *host)
{
	struct ahci_host_priv *hpriv = host->private_data;
	struct imx_ahci_priv *imxpriv = hpriv->plat_data;

	imx_sata_disable(hpriv);
	clk_disable_unprepare(imxpriv->sata_clk);
}