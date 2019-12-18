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
struct ata_host {struct ahci_host_priv* private_data; } ;
struct ahci_host_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  tegra_ahci_controller_deinit (struct ahci_host_priv*) ; 

__attribute__((used)) static void tegra_ahci_host_stop(struct ata_host *host)
{
	struct ahci_host_priv *hpriv = host->private_data;

	tegra_ahci_controller_deinit(hpriv);
}