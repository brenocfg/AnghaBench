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
struct zpci_dev {int /*<<< orphan*/  res_name; } ;
struct resource {unsigned long start; unsigned long end; unsigned long flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  iomem_resource ; 
 int /*<<< orphan*/  kfree (struct resource*) ; 
 struct resource* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ request_resource (int /*<<< orphan*/ *,struct resource*) ; 

__attribute__((used)) static struct resource *__alloc_res(struct zpci_dev *zdev, unsigned long start,
				    unsigned long size, unsigned long flags)
{
	struct resource *r;

	r = kzalloc(sizeof(*r), GFP_KERNEL);
	if (!r)
		return NULL;

	r->start = start;
	r->end = r->start + size - 1;
	r->flags = flags;
	r->name = zdev->res_name;

	if (request_resource(&iomem_resource, r)) {
		kfree(r);
		return NULL;
	}
	return r;
}