#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mpc52xx_ata_priv {unsigned int csel; } ;
struct ata_port {TYPE_1__* host; } ;
struct TYPE_2__ {struct mpc52xx_ata_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ata_sff_dev_select (struct ata_port*,unsigned int) ; 
 int /*<<< orphan*/  mpc52xx_ata_apply_timings (struct mpc52xx_ata_priv*,unsigned int) ; 

__attribute__((used)) static void
mpc52xx_ata_dev_select(struct ata_port *ap, unsigned int device)
{
	struct mpc52xx_ata_priv *priv = ap->host->private_data;

	if (device != priv->csel)
		mpc52xx_ata_apply_timings(priv, device);

	ata_sff_dev_select(ap, device);
}