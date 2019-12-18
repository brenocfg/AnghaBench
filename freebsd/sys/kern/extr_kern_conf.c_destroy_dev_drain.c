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
struct cdevsw {int /*<<< orphan*/  d_devs; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  dev_lock () ; 
 int /*<<< orphan*/  dev_unlock () ; 
 int /*<<< orphan*/  devmtx ; 
 int hz ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

void
destroy_dev_drain(struct cdevsw *csw)
{

	dev_lock();
	while (!LIST_EMPTY(&csw->d_devs)) {
		msleep(&csw->d_devs, &devmtx, PRIBIO, "devscd", hz/10);
	}
	dev_unlock();
}