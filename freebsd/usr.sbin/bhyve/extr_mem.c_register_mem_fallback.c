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
struct mem_range {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmio_rb_fallback ; 
 int register_mem_int (int /*<<< orphan*/ *,struct mem_range*) ; 

int
register_mem_fallback(struct mem_range *memp)
{

	return (register_mem_int(&mmio_rb_fallback, memp));
}