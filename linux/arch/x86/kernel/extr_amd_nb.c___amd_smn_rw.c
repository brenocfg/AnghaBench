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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {scalar_t__ num; } ;
struct TYPE_3__ {struct pci_dev* root; } ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_2__ amd_northbridges ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* node_to_amd_nb (scalar_t__) ; 
 int pci_read_config_dword (struct pci_dev*,int,int /*<<< orphan*/ *) ; 
 int pci_write_config_dword (struct pci_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,char*,...) ; 
 int /*<<< orphan*/  smn_mutex ; 

__attribute__((used)) static int __amd_smn_rw(u16 node, u32 address, u32 *value, bool write)
{
	struct pci_dev *root;
	int err = -ENODEV;

	if (node >= amd_northbridges.num)
		goto out;

	root = node_to_amd_nb(node)->root;
	if (!root)
		goto out;

	mutex_lock(&smn_mutex);

	err = pci_write_config_dword(root, 0x60, address);
	if (err) {
		pr_warn("Error programming SMN address 0x%x.\n", address);
		goto out_unlock;
	}

	err = (write ? pci_write_config_dword(root, 0x64, *value)
		     : pci_read_config_dword(root, 0x64, value));
	if (err)
		pr_warn("Error %s SMN address 0x%x.\n",
			(write ? "writing to" : "reading from"), address);

out_unlock:
	mutex_unlock(&smn_mutex);

out:
	return err;
}