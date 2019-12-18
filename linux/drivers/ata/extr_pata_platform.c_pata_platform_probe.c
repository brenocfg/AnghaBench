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
struct resource {int dummy; } ;
struct platform_device {int num_resources; int /*<<< orphan*/  dev; } ;
struct pata_platform_info {int /*<<< orphan*/  ioport_shift; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IORESOURCE_IO ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int __pata_platform_probe (int /*<<< orphan*/ *,struct resource*,struct resource*,struct resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct pata_platform_info* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pata_platform_sht ; 
 int /*<<< orphan*/  pio_mask ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pata_platform_probe(struct platform_device *pdev)
{
	struct resource *io_res;
	struct resource *ctl_res;
	struct resource *irq_res;
	struct pata_platform_info *pp_info = dev_get_platdata(&pdev->dev);

	/*
	 * Simple resource validation ..
	 */
	if ((pdev->num_resources != 3) && (pdev->num_resources != 2)) {
		dev_err(&pdev->dev, "invalid number of resources\n");
		return -EINVAL;
	}

	/*
	 * Get the I/O base first
	 */
	io_res = platform_get_resource(pdev, IORESOURCE_IO, 0);
	if (io_res == NULL) {
		io_res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
		if (unlikely(io_res == NULL))
			return -EINVAL;
	}

	/*
	 * Then the CTL base
	 */
	ctl_res = platform_get_resource(pdev, IORESOURCE_IO, 1);
	if (ctl_res == NULL) {
		ctl_res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
		if (unlikely(ctl_res == NULL))
			return -EINVAL;
	}

	/*
	 * And the IRQ
	 */
	irq_res = platform_get_resource(pdev, IORESOURCE_IRQ, 0);

	return __pata_platform_probe(&pdev->dev, io_res, ctl_res, irq_res,
				     pp_info ? pp_info->ioport_shift : 0,
				     pio_mask, &pata_platform_sht, false);
}