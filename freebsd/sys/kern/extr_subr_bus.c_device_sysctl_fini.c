#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
struct TYPE_3__ {int /*<<< orphan*/ * sysctl_tree; int /*<<< orphan*/  sysctl_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
device_sysctl_fini(device_t dev)
{
	if (dev->sysctl_tree == NULL)
		return;
	sysctl_ctx_free(&dev->sysctl_ctx);
	dev->sysctl_tree = NULL;
}