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
struct agp_memory {int /*<<< orphan*/  am_physical; int /*<<< orphan*/  am_id; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int pg_count; int /*<<< orphan*/  physical; int /*<<< orphan*/  key; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ agp_allocate ;

/* Variables and functions */
 struct agp_memory* AGP_ALLOC_MEMORY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int AGP_PAGE_SHIFT ; 
 int ENOMEM ; 

__attribute__((used)) static int
agp_allocate_user(device_t dev, agp_allocate *alloc)
{
	struct agp_memory *mem;

	mem = AGP_ALLOC_MEMORY(dev,
			       alloc->type,
			       alloc->pg_count << AGP_PAGE_SHIFT);
	if (mem) {
		alloc->key = mem->am_id;
		alloc->physical = mem->am_physical;
		return 0;
	} else {
		return ENOMEM;
	}
}