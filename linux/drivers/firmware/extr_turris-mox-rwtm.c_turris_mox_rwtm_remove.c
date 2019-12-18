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
struct platform_device {int dummy; } ;
struct mox_rwtm {int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_free_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mox_rwtm_attrs ; 
 struct mox_rwtm* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rwtm_to_kobj (struct mox_rwtm*) ; 
 int /*<<< orphan*/  sysfs_remove_files (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int turris_mox_rwtm_remove(struct platform_device *pdev)
{
	struct mox_rwtm *rwtm = platform_get_drvdata(pdev);

	sysfs_remove_files(rwtm_to_kobj(rwtm), mox_rwtm_attrs);
	kobject_put(rwtm_to_kobj(rwtm));
	mbox_free_channel(rwtm->mbox);

	return 0;
}