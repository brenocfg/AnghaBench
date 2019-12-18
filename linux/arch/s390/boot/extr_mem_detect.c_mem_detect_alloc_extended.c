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
typedef  int /*<<< orphan*/  u64 ;

/* Variables and functions */
 unsigned long ALIGN (scalar_t__,int) ; 
 int /*<<< orphan*/  CONFIG_BLK_DEV_INITRD ; 
 scalar_t__ ENTRIES_EXTENDED_MAX ; 
 scalar_t__ INITRD_SIZE ; 
 scalar_t__ INITRD_START ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ mem_safe_offset () ; 

__attribute__((used)) static void *mem_detect_alloc_extended(void)
{
	unsigned long offset = ALIGN(mem_safe_offset(), sizeof(u64));

	if (IS_ENABLED(CONFIG_BLK_DEV_INITRD) && INITRD_START && INITRD_SIZE &&
	    INITRD_START < offset + ENTRIES_EXTENDED_MAX)
		offset = ALIGN(INITRD_START + INITRD_SIZE, sizeof(u64));

	return (void *)offset;
}