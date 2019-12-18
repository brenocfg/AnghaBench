#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ priority; scalar_t__ is_alternate; } ;
typedef  TYPE_1__ backend_internal ;

/* Variables and functions */

__attribute__((used)) static int backend_sort_cmp(const void *a, const void *b)
{
	const backend_internal *backend_a = (const backend_internal *)(a);
	const backend_internal *backend_b = (const backend_internal *)(b);

	if (backend_b->priority == backend_a->priority) {
		if (backend_a->is_alternate)
			return -1;
		if (backend_b->is_alternate)
			return 1;
		return 0;
	}
	return (backend_b->priority - backend_a->priority);
}