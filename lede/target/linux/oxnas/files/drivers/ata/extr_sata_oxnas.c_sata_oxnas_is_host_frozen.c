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
struct sata_oxnas_host_priv {scalar_t__ port_frozen; scalar_t__ port_in_eh; } ;
struct ata_host {struct sata_oxnas_host_priv* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  smp_rmb () ; 

__attribute__((used)) static inline int sata_oxnas_is_host_frozen(struct ata_host *ah)
{
	struct sata_oxnas_host_priv *hd = ah->private_data;

	smp_rmb();
	return hd->port_in_eh || hd->port_frozen;
}