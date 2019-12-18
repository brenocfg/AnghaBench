#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cache_info {int ways; unsigned long way_incr; } ;
struct TYPE_2__ {struct cache_info dcache; } ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 TYPE_1__ boot_cpu_data ; 

__attribute__((used)) static void __flush_cache_one(unsigned long addr, unsigned long phys,
			       unsigned long exec_offset)
{
	int way_count;
	unsigned long base_addr = addr;
	struct cache_info *dcache;
	unsigned long way_incr;
	unsigned long a, ea, p;
	unsigned long temp_pc;

	dcache = &boot_cpu_data.dcache;
	/* Write this way for better assembly. */
	way_count = dcache->ways;
	way_incr = dcache->way_incr;

	/*
	 * Apply exec_offset (i.e. branch to P2 if required.).
	 *
	 * FIXME:
	 *
	 *	If I write "=r" for the (temp_pc), it puts this in r6 hence
	 *	trashing exec_offset before it's been added on - why?  Hence
	 *	"=&r" as a 'workaround'
	 */
	asm volatile("mov.l 1f, %0\n\t"
		     "add   %1, %0\n\t"
		     "jmp   @%0\n\t"
		     "nop\n\t"
		     ".balign 4\n\t"
		     "1:  .long 2f\n\t"
		     "2:\n" : "=&r" (temp_pc) : "r" (exec_offset));

	/*
	 * We know there will be >=1 iteration, so write as do-while to avoid
	 * pointless nead-of-loop check for 0 iterations.
	 */
	do {
		ea = base_addr + PAGE_SIZE;
		a = base_addr;
		p = phys;

		do {
			*(volatile unsigned long *)a = p;
			/*
			 * Next line: intentionally not p+32, saves an add, p
			 * will do since only the cache tag bits need to
			 * match.
			 */
			*(volatile unsigned long *)(a+32) = p;
			a += 64;
			p += 64;
		} while (a < ea);

		base_addr += way_incr;
	} while (--way_count != 0);
}