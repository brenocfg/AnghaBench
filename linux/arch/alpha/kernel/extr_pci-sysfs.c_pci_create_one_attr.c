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
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct pci_dev {TYPE_2__ dev; int /*<<< orphan*/ * resource; } ;
struct TYPE_3__ {char* name; int mode; } ;
struct bin_attribute {size_t size; int /*<<< orphan*/ * private; TYPE_1__ attr; int /*<<< orphan*/  mmap; } ;

/* Variables and functions */
 int S_IRUSR ; 
 int S_IWUSR ; 
 int /*<<< orphan*/  pci_mmap_resource_dense ; 
 int /*<<< orphan*/  pci_mmap_resource_sparse ; 
 size_t pci_resource_len (struct pci_dev*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,char*) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,struct bin_attribute*) ; 

__attribute__((used)) static int pci_create_one_attr(struct pci_dev *pdev, int num, char *name,
			       char *suffix, struct bin_attribute *res_attr,
			       unsigned long sparse)
{
	size_t size = pci_resource_len(pdev, num);

	sprintf(name, "resource%d%s", num, suffix);
	res_attr->mmap = sparse ? pci_mmap_resource_sparse :
				  pci_mmap_resource_dense;
	res_attr->attr.name = name;
	res_attr->attr.mode = S_IRUSR | S_IWUSR;
	res_attr->size = sparse ? size << 5 : size;
	res_attr->private = &pdev->resource[num];
	return sysfs_create_bin_file(&pdev->dev.kobj, res_attr);
}