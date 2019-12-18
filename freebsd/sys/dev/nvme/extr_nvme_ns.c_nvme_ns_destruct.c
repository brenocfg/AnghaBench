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
struct nvme_namespace {int /*<<< orphan*/ * cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ *) ; 

void nvme_ns_destruct(struct nvme_namespace *ns)
{

	if (ns->cdev != NULL)
		destroy_dev(ns->cdev);
}