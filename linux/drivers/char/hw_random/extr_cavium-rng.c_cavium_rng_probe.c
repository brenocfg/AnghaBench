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
struct pci_device_id {int dummy; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct cavium_rng_pf {int /*<<< orphan*/  control_status; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int THUNDERX_RNM_ENT_EN ; 
 int THUNDERX_RNM_RNG_EN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct cavium_rng_pf* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int pci_enable_sriov (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,struct cavium_rng_pf*) ; 
 int /*<<< orphan*/  pcim_iomap (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeq (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cavium_rng_probe(struct pci_dev *pdev,
			const struct pci_device_id *id)
{
	struct	cavium_rng_pf *rng;
	int	iov_err;

	rng = devm_kzalloc(&pdev->dev, sizeof(*rng), GFP_KERNEL);
	if (!rng)
		return -ENOMEM;

	/*Map the RNG control */
	rng->control_status = pcim_iomap(pdev, 0, 0);
	if (!rng->control_status) {
		dev_err(&pdev->dev,
			"Error iomap failed retrieving control_status.\n");
		return -ENOMEM;
	}

	/* Enable the RNG hardware and entropy source */
	writeq(THUNDERX_RNM_RNG_EN | THUNDERX_RNM_ENT_EN,
		rng->control_status);

	pci_set_drvdata(pdev, rng);

	/* Enable the Cavium RNG as a VF */
	iov_err = pci_enable_sriov(pdev, 1);
	if (iov_err != 0) {
		/* Disable the RNG hardware and entropy source */
		writeq(0, rng->control_status);
		dev_err(&pdev->dev,
			"Error initializing RNG virtual function,(%i).\n",
			iov_err);
		return iov_err;
	}

	return 0;
}