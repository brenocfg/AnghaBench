#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* device_t ;
typedef  TYPE_2__* devclass_t ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {scalar_t__ nameunit; int /*<<< orphan*/ * sysctl_tree; TYPE_2__* devclass; } ;

/* Variables and functions */
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_rename_oid (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
device_sysctl_update(device_t dev)
{
	devclass_t dc = dev->devclass;

	if (dev->sysctl_tree == NULL)
		return;
	sysctl_rename_oid(dev->sysctl_tree, dev->nameunit + strlen(dc->name));
}