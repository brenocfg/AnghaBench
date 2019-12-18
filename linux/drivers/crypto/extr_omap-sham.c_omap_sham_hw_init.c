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
struct omap_sham_dev {scalar_t__ err; int /*<<< orphan*/  flags; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAGS_INIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_sham_hw_init(struct omap_sham_dev *dd)
{
	int err;

	err = pm_runtime_get_sync(dd->dev);
	if (err < 0) {
		dev_err(dd->dev, "failed to get sync: %d\n", err);
		return err;
	}

	if (!test_bit(FLAGS_INIT, &dd->flags)) {
		set_bit(FLAGS_INIT, &dd->flags);
		dd->err = 0;
	}

	return 0;
}