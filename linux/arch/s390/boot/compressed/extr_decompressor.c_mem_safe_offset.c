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
struct TYPE_2__ {scalar_t__ bss_size; scalar_t__ image_size; scalar_t__ default_lma; } ;

/* Variables and functions */
 scalar_t__ decompress_offset ; 
 unsigned long max (scalar_t__,scalar_t__) ; 
 TYPE_1__ vmlinux ; 

unsigned long mem_safe_offset(void)
{
	/*
	 * due to 4MB HEAD_SIZE for bzip2
	 * 'decompress_offset + vmlinux.image_size' could be larger than
	 * kernel at final position + its .bss, so take the larger of two
	 */
	return max(decompress_offset + vmlinux.image_size,
		   vmlinux.default_lma + vmlinux.image_size + vmlinux.bss_size);
}