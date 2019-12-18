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
struct TYPE_3__ {void const* addr; } ;
typedef  TYPE_1__ isc_backtrace_symmap_t ;

/* Variables and functions */
 int isc__backtrace_nsymbols ; 
 TYPE_1__* isc__backtrace_symtable ; 

__attribute__((used)) static int
symtbl_compare(const void *addr, const void *entryarg) {
	const isc_backtrace_symmap_t *entry = entryarg;
	const isc_backtrace_symmap_t *end =
		&isc__backtrace_symtable[isc__backtrace_nsymbols - 1];

	if (isc__backtrace_nsymbols == 1 || entry == end) {
		if (addr >= entry->addr) {
			/*
			 * If addr is equal to or larger than that of the last
			 * entry of the table, we cannot be sure if this is
			 * within a valid range so we consider it valid.
			 */
			return (0);
		}
		return (-1);
	}

	/* entry + 1 is a valid entry from now on. */
	if (addr < entry->addr)
		return (-1);
	else if (addr >= (entry + 1)->addr)
		return (1);
	return (0);
}