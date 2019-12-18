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
typedef  scalar_t__ vm_offset_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  bcopy (void const*,void*,size_t const) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ stage_offset ; 
 int stage_offset_set ; 
 scalar_t__ staging ; 
 scalar_t__ staging_end ; 

ssize_t
efi_copyin(const void *src, vm_offset_t dest, const size_t len)
{

	if (!stage_offset_set) {
		stage_offset = (vm_offset_t)staging - dest;
		stage_offset_set = 1;
	}

	/* XXX: Callers do not check for failure. */
	if (dest + stage_offset + len > staging_end) {
		errno = ENOMEM;
		return (-1);
	}
	bcopy(src, (void *)(dest + stage_offset), len);
	return (len);
}