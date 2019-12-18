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
 struct exception_table_entry const __copy_user_fixup_ex ; 
 int /*<<< orphan*/  copy_user_memcpy ; 
 int /*<<< orphan*/  copy_user_memcpy_end ; 

__attribute__((used)) static const struct exception_table_entry *check_exception_ranges(unsigned long addr)
{
	if ((addr >= (unsigned long)&copy_user_memcpy) &&
	    (addr <= (unsigned long)&copy_user_memcpy_end))
		return &__copy_user_fixup_ex;

	return NULL;
}