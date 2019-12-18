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
struct amd64_pvt {int /*<<< orphan*/  F2; int /*<<< orphan*/  F1; int /*<<< orphan*/  F6; int /*<<< orphan*/  F0; scalar_t__ umc; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_dev_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_mc_sibling_devs(struct amd64_pvt *pvt)
{
	if (pvt->umc) {
		pci_dev_put(pvt->F0);
		pci_dev_put(pvt->F6);
	} else {
		pci_dev_put(pvt->F1);
		pci_dev_put(pvt->F2);
	}
}