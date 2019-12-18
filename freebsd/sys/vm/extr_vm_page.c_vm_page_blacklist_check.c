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
typedef  int /*<<< orphan*/  vm_paddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  bootverbose ; 
 int /*<<< orphan*/  vm_page_blacklist_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_blacklist_next (char**,char*) ; 

__attribute__((used)) static void
vm_page_blacklist_check(char *list, char *end)
{
	vm_paddr_t pa;
	char *next;

	next = list;
	while (next != NULL) {
		if ((pa = vm_page_blacklist_next(&next, end)) == 0)
			continue;
		vm_page_blacklist_add(pa, bootverbose);
	}
}