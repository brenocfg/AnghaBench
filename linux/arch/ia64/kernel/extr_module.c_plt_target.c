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
typedef  int uint64_t ;
struct plt_entry {scalar_t__* bundle; } ;

/* Variables and functions */

unsigned long
plt_target (struct plt_entry *plt)
{
	uint64_t b0, b1, *b = (uint64_t *) plt->bundle[1];
	long off;

	b0 = b[0]; b1 = b[1];
	off = (  ((b1 & 0x00fffff000000000UL) >> 36)		/* imm20b -> bit 0 */
	       | ((b0 >> 48) << 20) | ((b1 & 0x7fffffUL) << 36)	/* imm39 -> bit 20 */
	       | ((b1 & 0x0800000000000000UL) << 0));		/* i -> bit 59 */
	return (long) plt->bundle[1] + 16*off;
}