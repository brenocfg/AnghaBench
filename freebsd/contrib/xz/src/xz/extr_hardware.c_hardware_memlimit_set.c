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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int memlimit_compress ; 
 int memlimit_decompress ; 
 int total_ram ; 

extern void
hardware_memlimit_set(uint64_t new_memlimit,
		bool set_compress, bool set_decompress, bool is_percentage)
{
	if (is_percentage) {
		assert(new_memlimit > 0);
		assert(new_memlimit <= 100);
		new_memlimit = (uint32_t)new_memlimit * total_ram / 100;
	}

	if (set_compress)
		memlimit_compress = new_memlimit;

	if (set_decompress)
		memlimit_decompress = new_memlimit;

	return;
}