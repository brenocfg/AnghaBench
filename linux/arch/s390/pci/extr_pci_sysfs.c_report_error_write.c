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
struct zpci_report_error_header {int dummy; } ;
struct zpci_dev {int /*<<< orphan*/  fid; int /*<<< orphan*/  fh; } ;
struct pci_dev {int dummy; } ;
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct device {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 int EINVAL ; 
 struct device* kobj_to_dev (struct kobject*) ; 
 int sclp_pci_report (struct zpci_report_error_header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 struct zpci_dev* to_zpci (struct pci_dev*) ; 

__attribute__((used)) static ssize_t report_error_write(struct file *filp, struct kobject *kobj,
				  struct bin_attribute *attr, char *buf,
				  loff_t off, size_t count)
{
	struct zpci_report_error_header *report = (void *) buf;
	struct device *dev = kobj_to_dev(kobj);
	struct pci_dev *pdev = to_pci_dev(dev);
	struct zpci_dev *zdev = to_zpci(pdev);
	int ret;

	if (off || (count < sizeof(*report)))
		return -EINVAL;

	ret = sclp_pci_report(report, zdev->fh, zdev->fid);

	return ret ? ret : count;
}