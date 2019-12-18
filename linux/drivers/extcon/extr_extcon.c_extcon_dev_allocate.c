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
struct extcon_dev {unsigned int const* supported_cable; scalar_t__ max_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct extcon_dev* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct extcon_dev* kzalloc (int,int /*<<< orphan*/ ) ; 

struct extcon_dev *extcon_dev_allocate(const unsigned int *supported_cable)
{
	struct extcon_dev *edev;

	if (!supported_cable)
		return ERR_PTR(-EINVAL);

	edev = kzalloc(sizeof(*edev), GFP_KERNEL);
	if (!edev)
		return ERR_PTR(-ENOMEM);

	edev->max_supported = 0;
	edev->supported_cable = supported_cable;

	return edev;
}