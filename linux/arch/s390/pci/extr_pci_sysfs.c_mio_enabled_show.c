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
struct zpci_dev {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*) ; 
 int /*<<< orphan*/  to_pci_dev (struct device*) ; 
 struct zpci_dev* to_zpci (int /*<<< orphan*/ ) ; 
 scalar_t__ zpci_use_mio (struct zpci_dev*) ; 

__attribute__((used)) static ssize_t mio_enabled_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct zpci_dev *zdev = to_zpci(to_pci_dev(dev));

	return sprintf(buf, zpci_use_mio(zdev) ? "1\n" : "0\n");
}