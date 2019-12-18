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
typedef  unsigned long Elf_Addr ;

/* Variables and functions */
 int ENOEXEC ; 

__attribute__((used)) static int apply_rela_bits(Elf_Addr loc, Elf_Addr val,
			   int sign, int bits, int shift)
{
	unsigned long umax;
	long min, max;

	if (val & ((1UL << shift) - 1))
		return -ENOEXEC;
	if (sign) {
		val = (Elf_Addr)(((long) val) >> shift);
		min = -(1L << (bits - 1));
		max = (1L << (bits - 1)) - 1;
		if ((long) val < min || (long) val > max)
			return -ENOEXEC;
	} else {
		val >>= shift;
		umax = ((1UL << (bits - 1)) << 1) - 1;
		if ((unsigned long) val > umax)
			return -ENOEXEC;
	}

	if (bits == 8)
		*(unsigned char *) loc = val;
	else if (bits == 12)
		*(unsigned short *) loc = (val & 0xfff) |
			(*(unsigned short *) loc & 0xf000);
	else if (bits == 16)
		*(unsigned short *) loc = val;
	else if (bits == 20)
		*(unsigned int *) loc = (val & 0xfff) << 16 |
			(val & 0xff000) >> 4 |
			(*(unsigned int *) loc & 0xf00000ff);
	else if (bits == 32)
		*(unsigned int *) loc = val;
	else if (bits == 64)
		*(unsigned long *) loc = val;
	return 0;
}