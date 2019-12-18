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
struct zpci_dev {scalar_t__ domain; } ;

/* Variables and functions */
 scalar_t__ ZPCI_NR_DEVICES ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpci_domain ; 
 int /*<<< orphan*/  zpci_domain_lock ; 

__attribute__((used)) static void zpci_free_domain(struct zpci_dev *zdev)
{
	if (zdev->domain >= ZPCI_NR_DEVICES)
		return;

	spin_lock(&zpci_domain_lock);
	clear_bit(zdev->domain, zpci_domain);
	spin_unlock(&zpci_domain_lock);
}