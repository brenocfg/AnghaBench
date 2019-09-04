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
typedef  int const uint32_t ;
struct TYPE_3__ {int item_size; } ;
typedef  TYPE_1__ git_pool ;

/* Variables and functions */

__attribute__((used)) static uint32_t alloc_size(git_pool *pool, uint32_t count)
{
	const uint32_t align = sizeof(void *) - 1;

	if (pool->item_size > 1) {
		const uint32_t item_size = (pool->item_size + align) & ~align;
		return item_size * count;
	}

	return (count + align) & ~align;
}