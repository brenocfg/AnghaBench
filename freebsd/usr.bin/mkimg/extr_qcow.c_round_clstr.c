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

/* Variables and functions */
 unsigned long clstr_log2sz ; 

__attribute__((used)) static uint64_t
round_clstr(uint64_t ofs)
{
	uint64_t clstrsz;

	clstrsz = 1UL << clstr_log2sz;
	return ((ofs + clstrsz - 1) & ~(clstrsz - 1));
}