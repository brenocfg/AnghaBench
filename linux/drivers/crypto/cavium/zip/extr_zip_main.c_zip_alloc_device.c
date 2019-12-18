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
struct zip_device {int index; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_ZIP_DEVICES ; 
 struct zip_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct zip_device** zip_dev ; 

__attribute__((used)) static struct zip_device *zip_alloc_device(struct pci_dev *pdev)
{
	struct zip_device *zip = NULL;
	int idx;

	for (idx = 0; idx < MAX_ZIP_DEVICES; idx++) {
		if (!zip_dev[idx])
			break;
	}

	/* To ensure that the index is within the limit */
	if (idx < MAX_ZIP_DEVICES)
		zip = devm_kzalloc(&pdev->dev, sizeof(*zip), GFP_KERNEL);

	if (!zip)
		return NULL;

	zip_dev[idx] = zip;
	zip->index = idx;
	return zip;
}