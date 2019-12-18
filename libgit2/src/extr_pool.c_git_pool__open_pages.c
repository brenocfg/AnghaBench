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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ git_pool_page ;
struct TYPE_5__ {TYPE_1__* pages; } ;
typedef  TYPE_2__ git_pool ;

/* Variables and functions */

uint32_t git_pool__open_pages(git_pool *pool)
{
	uint32_t ct = 0;
	git_pool_page *scan;
	for (scan = pool->pages; scan != NULL; scan = scan->next) ct++;
	return ct;
}