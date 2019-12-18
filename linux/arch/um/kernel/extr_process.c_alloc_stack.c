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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long __get_free_pages (int /*<<< orphan*/ ,int) ; 

unsigned long alloc_stack(int order, int atomic)
{
	unsigned long page;
	gfp_t flags = GFP_KERNEL;

	if (atomic)
		flags = GFP_ATOMIC;
	page = __get_free_pages(flags, order);

	return page;
}