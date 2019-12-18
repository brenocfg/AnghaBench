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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENODEV ; 
 int devm_hwrng_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  powernv_hwrng ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int powernv_rng_probe(struct platform_device *pdev)
{
	int rc;

	rc = devm_hwrng_register(&pdev->dev, &powernv_hwrng);
	if (rc) {
		/* We only register one device, ignore any others */
		if (rc == -EEXIST)
			rc = -ENODEV;

		return rc;
	}

	pr_info("Registered powernv hwrng.\n");

	return 0;
}