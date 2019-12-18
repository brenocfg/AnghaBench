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
 unsigned int FIQ_OFFSET ; 
 int /*<<< orphan*/  cache_is_vipt_nonaliasing () ; 
 int /*<<< orphan*/  flush_icache_range (int,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned int) ; 
 void* vectors_page ; 

void set_fiq_handler(void *start, unsigned int length)
{
	void *base = vectors_page;
	unsigned offset = FIQ_OFFSET;

	memcpy(base + offset, start, length);
	if (!cache_is_vipt_nonaliasing())
		flush_icache_range((unsigned long)base + offset, offset +
				   length);
	flush_icache_range(0xffff0000 + offset, 0xffff0000 + offset + length);
}