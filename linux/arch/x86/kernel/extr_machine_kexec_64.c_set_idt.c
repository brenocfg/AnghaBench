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
typedef  int /*<<< orphan*/  u16 ;
struct desc_ptr {unsigned long address; int /*<<< orphan*/  size; } ;

/* Variables and functions */

__attribute__((used)) static void set_idt(void *newidt, u16 limit)
{
	struct desc_ptr curidt;

	/* x86-64 supports unaliged loads & stores */
	curidt.size    = limit;
	curidt.address = (unsigned long)newidt;

	__asm__ __volatile__ (
		"lidtq %0\n"
		: : "m" (curidt)
		);
}