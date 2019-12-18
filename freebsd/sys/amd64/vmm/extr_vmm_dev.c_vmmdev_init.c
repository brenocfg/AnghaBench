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
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_allow_flag ; 
 int /*<<< orphan*/  prison_add_allow (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vmmdev_mtx ; 

void
vmmdev_init(void)
{
	mtx_init(&vmmdev_mtx, "vmm device mutex", NULL, MTX_DEF);
	pr_allow_flag = prison_add_allow(NULL, "vmm", NULL,
	    "Allow use of vmm in a jail.");
}