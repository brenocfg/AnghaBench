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
struct device {int dummy; } ;
struct dca_provider {int /*<<< orphan*/  cd; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  dca_class ; 
 struct device* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int dca_sysfs_add_req(struct dca_provider *dca, struct device *dev, int slot)
{
	struct device *cd;
	static int req_count;

	cd = device_create(dca_class, dca->cd, MKDEV(0, slot + 1), NULL,
			   "requester%d", req_count++);
	if (IS_ERR(cd))
		return PTR_ERR(cd);
	return 0;
}