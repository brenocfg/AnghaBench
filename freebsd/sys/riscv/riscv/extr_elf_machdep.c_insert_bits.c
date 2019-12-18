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
typedef  int uint32_t ;

/* Variables and functions */
 int gen_bitmask (int,int) ; 

__attribute__((used)) static uint32_t
insert_bits(uint32_t d, uint32_t s, int msb, int lsb)
{
	uint32_t mask;

	mask = gen_bitmask(msb, lsb);

	d &= ~mask;

	s <<= lsb;
	s &= mask;

	return (d | s);
}