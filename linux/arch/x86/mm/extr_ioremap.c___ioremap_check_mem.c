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
typedef  scalar_t__ u64 ;
struct ioremap_desc {int dummy; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  __ioremap_collect_map_flags ; 
 int /*<<< orphan*/  memset (struct ioremap_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  walk_mem_res (scalar_t__,scalar_t__,struct ioremap_desc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __ioremap_check_mem(resource_size_t addr, unsigned long size,
				struct ioremap_desc *desc)
{
	u64 start, end;

	start = (u64)addr;
	end = start + size - 1;
	memset(desc, 0, sizeof(struct ioremap_desc));

	walk_mem_res(start, end, desc, __ioremap_collect_map_flags);
}