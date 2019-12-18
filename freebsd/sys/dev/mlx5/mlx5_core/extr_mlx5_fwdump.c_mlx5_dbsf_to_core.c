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
struct pci_dev {int dummy; } ;
struct mlx5_tool_addr {int /*<<< orphan*/  func; int /*<<< orphan*/  slot; int /*<<< orphan*/  bus; int /*<<< orphan*/  domain; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_2__ {scalar_t__ bsdclass; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 scalar_t__ device_get_devclass (int /*<<< orphan*/ *) ; 
 struct pci_dev* device_get_softc (int /*<<< orphan*/ *) ; 
 TYPE_1__ mlx5_core_driver ; 
 int /*<<< orphan*/ * pci_find_dbsf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx5_core_dev* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static int
mlx5_dbsf_to_core(const struct mlx5_tool_addr *devaddr,
    struct mlx5_core_dev **mdev)
{
	device_t dev;
	struct pci_dev *pdev;

	dev = pci_find_dbsf(devaddr->domain, devaddr->bus, devaddr->slot,
	    devaddr->func);
	if (dev == NULL)
		return (ENOENT);
	if (device_get_devclass(dev) != mlx5_core_driver.bsdclass)
		return (EINVAL);
	pdev = device_get_softc(dev);
	*mdev = pci_get_drvdata(pdev);
	if (*mdev == NULL)
		return (ENOENT);
	return (0);
}