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
struct resource {int dummy; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 struct resource* XENMEM_ALLOC (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,size_t) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 

struct resource *
xenmem_alloc(device_t dev, int *res_id, size_t size)
{
	device_t parent;

	parent = device_get_parent(dev);
	if (parent == NULL)
		return (NULL);
	return (XENMEM_ALLOC(parent, dev, res_id, size));
}