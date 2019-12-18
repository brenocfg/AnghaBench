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
struct hwrng {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_hwrng_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct hwrng**) ; 
 struct hwrng** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct hwrng**) ; 
 int hwrng_register (struct hwrng*) ; 

int devm_hwrng_register(struct device *dev, struct hwrng *rng)
{
	struct hwrng **ptr;
	int error;

	ptr = devres_alloc(devm_hwrng_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return -ENOMEM;

	error = hwrng_register(rng);
	if (error) {
		devres_free(ptr);
		return error;
	}

	*ptr = rng;
	devres_add(dev, ptr);
	return 0;
}