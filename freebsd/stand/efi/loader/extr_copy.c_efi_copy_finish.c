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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ stage_offset ; 
 scalar_t__ staging ; 
 scalar_t__ staging_end ; 

void
efi_copy_finish(void)
{
	uint64_t	*src, *dst, *last;

	src = (uint64_t *)(uintptr_t)staging;
	dst = (uint64_t *)(uintptr_t)(staging - stage_offset);
	last = (uint64_t *)(uintptr_t)staging_end;

	while (src < last)
		*dst++ = *src++;
}