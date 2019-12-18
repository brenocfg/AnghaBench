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
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  ffs_susp_cdevsw ; 
 int /*<<< orphan*/  ffs_susp_dev ; 
 int /*<<< orphan*/  ffs_susp_lock ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 

void
ffs_susp_initialize(void)
{

	sx_init(&ffs_susp_lock, "ffs_susp");
	ffs_susp_dev = make_dev(&ffs_susp_cdevsw, 0, UID_ROOT, GID_WHEEL, 0600,
	    "ufssuspend");
}