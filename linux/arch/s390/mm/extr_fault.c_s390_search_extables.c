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
struct exception_table_entry {int dummy; } ;

/* Variables and functions */
 scalar_t__ __start_dma_ex_table ; 
 scalar_t__ __stop_dma_ex_table ; 
 struct exception_table_entry* search_exception_tables (unsigned long) ; 
 struct exception_table_entry* search_extable (scalar_t__,scalar_t__,unsigned long) ; 

const struct exception_table_entry *s390_search_extables(unsigned long addr)
{
	const struct exception_table_entry *fixup;

	fixup = search_extable(__start_dma_ex_table,
			       __stop_dma_ex_table - __start_dma_ex_table,
			       addr);
	if (!fixup)
		fixup = search_exception_tables(addr);
	return fixup;
}