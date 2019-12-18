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

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_ioat_cdev ; 
 int /*<<< orphan*/  ioat_cdevsw ; 
 int /*<<< orphan*/ * make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
enable_ioat_test(bool enable)
{

	mtx_assert(&Giant, MA_OWNED);

	if (enable && g_ioat_cdev == NULL) {
		g_ioat_cdev = make_dev(&ioat_cdevsw, 0, UID_ROOT, GID_WHEEL,
		    0600, "ioat_test");
	} else if (!enable && g_ioat_cdev != NULL) {
		destroy_dev(g_ioat_cdev);
		g_ioat_cdev = NULL;
	}
	return (0);
}