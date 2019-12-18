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
 unsigned long KSEG0 ; 
 unsigned long KSEGX (unsigned long) ; 
 unsigned long ST0_IEC ; 
 unsigned long ST0_ISC ; 
 unsigned long dcache_size ; 
 unsigned long read_c0_status () ; 
 int /*<<< orphan*/  write_c0_status (unsigned long) ; 

__attribute__((used)) static void r3k_flush_dcache_range(unsigned long start, unsigned long end)
{
	unsigned long size, i, flags;
	volatile unsigned char *p;

	size = end - start;
	if (size > dcache_size || KSEGX(start) != KSEG0) {
		start = KSEG0;
		size = dcache_size;
	}
	p = (char *)start;

	flags = read_c0_status();

	/* isolate cache space */
	write_c0_status((ST0_ISC|flags)&~ST0_IEC);

	for (i = 0; i < size; i += 0x080) {
		asm(	"sb\t$0, 0x000(%0)\n\t"
			"sb\t$0, 0x004(%0)\n\t"
			"sb\t$0, 0x008(%0)\n\t"
			"sb\t$0, 0x00c(%0)\n\t"
			"sb\t$0, 0x010(%0)\n\t"
			"sb\t$0, 0x014(%0)\n\t"
			"sb\t$0, 0x018(%0)\n\t"
			"sb\t$0, 0x01c(%0)\n\t"
			"sb\t$0, 0x020(%0)\n\t"
			"sb\t$0, 0x024(%0)\n\t"
			"sb\t$0, 0x028(%0)\n\t"
			"sb\t$0, 0x02c(%0)\n\t"
			"sb\t$0, 0x030(%0)\n\t"
			"sb\t$0, 0x034(%0)\n\t"
			"sb\t$0, 0x038(%0)\n\t"
			"sb\t$0, 0x03c(%0)\n\t"
			"sb\t$0, 0x040(%0)\n\t"
			"sb\t$0, 0x044(%0)\n\t"
			"sb\t$0, 0x048(%0)\n\t"
			"sb\t$0, 0x04c(%0)\n\t"
			"sb\t$0, 0x050(%0)\n\t"
			"sb\t$0, 0x054(%0)\n\t"
			"sb\t$0, 0x058(%0)\n\t"
			"sb\t$0, 0x05c(%0)\n\t"
			"sb\t$0, 0x060(%0)\n\t"
			"sb\t$0, 0x064(%0)\n\t"
			"sb\t$0, 0x068(%0)\n\t"
			"sb\t$0, 0x06c(%0)\n\t"
			"sb\t$0, 0x070(%0)\n\t"
			"sb\t$0, 0x074(%0)\n\t"
			"sb\t$0, 0x078(%0)\n\t"
			"sb\t$0, 0x07c(%0)\n\t"
			: : "r" (p) );
		p += 0x080;
	}

	write_c0_status(flags);
}