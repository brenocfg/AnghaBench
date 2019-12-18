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
struct occ {int /*<<< orphan*/  idx; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  occ_ida ; 
 int /*<<< orphan*/  occ_unregister_child ; 
 struct occ* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int occ_remove(struct platform_device *pdev)
{
	struct occ *occ = platform_get_drvdata(pdev);

	misc_deregister(&occ->mdev);

	device_for_each_child(&pdev->dev, NULL, occ_unregister_child);

	ida_simple_remove(&occ_ida, occ->idx);

	return 0;
}