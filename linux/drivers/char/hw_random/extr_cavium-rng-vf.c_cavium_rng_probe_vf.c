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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int quality; int /*<<< orphan*/  read; int /*<<< orphan*/  name; } ;
struct cavium_rng {TYPE_1__ ops; int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cavium_rng_read ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int devm_hwrng_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  devm_kasprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct cavium_rng* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct cavium_rng*) ; 
 int /*<<< orphan*/  pcim_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cavium_rng_probe_vf(struct	pci_dev		*pdev,
			 const struct	pci_device_id	*id)
{
	struct	cavium_rng *rng;
	int	ret;

	rng = devm_kzalloc(&pdev->dev, sizeof(*rng), GFP_KERNEL);
	if (!rng)
		return -ENOMEM;

	/* Map the RNG result */
	rng->result = pcim_iomap(pdev, 0, 0);
	if (!rng->result) {
		dev_err(&pdev->dev, "Error iomap failed retrieving result.\n");
		return -ENOMEM;
	}

	rng->ops.name = devm_kasprintf(&pdev->dev, GFP_KERNEL,
				       "cavium-rng-%s", dev_name(&pdev->dev));
	if (!rng->ops.name)
		return -ENOMEM;

	rng->ops.read    = cavium_rng_read;
	rng->ops.quality = 1000;

	pci_set_drvdata(pdev, rng);

	ret = devm_hwrng_register(&pdev->dev, &rng->ops);
	if (ret) {
		dev_err(&pdev->dev, "Error registering device as HWRNG.\n");
		return ret;
	}

	return 0;
}