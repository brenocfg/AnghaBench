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
struct TYPE_2__ {int /*<<< orphan*/  msi_priv_data; } ;
struct msi_desc {TYPE_1__ platform; } ;
struct device {int /*<<< orphan*/  msi_domain; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_DEV_MSIS ; 
 int /*<<< orphan*/  dev_to_msi_list (struct device*) ; 
 struct msi_desc* first_msi_entry (struct device*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_domain_free_irqs (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  platform_msi_free_descs (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_msi_free_priv_data (int /*<<< orphan*/ ) ; 

void platform_msi_domain_free_irqs(struct device *dev)
{
	if (!list_empty(dev_to_msi_list(dev))) {
		struct msi_desc *desc;

		desc = first_msi_entry(dev);
		platform_msi_free_priv_data(desc->platform.msi_priv_data);
	}

	msi_domain_free_irqs(dev->msi_domain, dev);
	platform_msi_free_descs(dev, 0, MAX_DEV_MSIS);
}