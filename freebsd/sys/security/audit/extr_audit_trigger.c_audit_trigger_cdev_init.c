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
 int /*<<< orphan*/  AUDITDEV_FILENAME ; 
 int /*<<< orphan*/  GID_KMEM ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  audit_cdevsw ; 
 int /*<<< orphan*/  audit_dev ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
audit_trigger_cdev_init(void *unused)
{

	/* Create the special device file. */
	audit_dev = make_dev(&audit_cdevsw, 0, UID_ROOT, GID_KMEM, 0600,
	    AUDITDEV_FILENAME);
}