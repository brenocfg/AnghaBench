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
typedef  int vm_offset_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  invlpg (int) ; 
 int /*<<< orphan*/  pmap_kremove (int) ; 
 int round_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
table_unmap(void *data, vm_offset_t length)
{
	vm_offset_t va, off;

	va = (vm_offset_t)data;
	off = va & PAGE_MASK;
	length = round_page(length + off);
	va &= ~PAGE_MASK;
	while (length > 0) {
		pmap_kremove(va);
		invlpg(va);
		va += PAGE_SIZE;
		length -= PAGE_SIZE;
	}
}