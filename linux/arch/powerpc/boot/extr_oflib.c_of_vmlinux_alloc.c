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

/* Variables and functions */
 scalar_t__ _end ; 
 scalar_t__ _start ; 
 int /*<<< orphan*/  fatal (char*) ; 
 void* malloc (unsigned long) ; 
 scalar_t__ of_claim (unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,unsigned long,unsigned long,unsigned long,unsigned long) ; 

void *of_vmlinux_alloc(unsigned long size)
{
	unsigned long start = (unsigned long)_start, end = (unsigned long)_end;
	unsigned long addr;
	void *p;

	/* With some older POWER4 firmware we need to claim the area the kernel
	 * will reside in.  Newer firmwares don't need this so we just ignore
	 * the return value.
	 */
	addr = (unsigned long) of_claim(start, end - start, 0);
	printf("Trying to claim from 0x%lx to 0x%lx (0x%lx) got %lx\r\n",
	       start, end, end - start, addr);

	p = malloc(size);
	if (!p)
		fatal("Can't allocate memory for kernel image!\n\r");

	return p;
}