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
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 void stub1 () ; 

__attribute__((used)) static void
link_elf_invoke_ctors(caddr_t addr, size_t size)
{
	void (**ctor)(void);
	size_t i, cnt;

	if (addr == NULL || size == 0)
		return;
	cnt = size / sizeof(*ctor);
	ctor = (void *)addr;
	for (i = 0; i < cnt; i++) {
		if (ctor[i] != NULL)
			(*ctor[i])();
	}
}