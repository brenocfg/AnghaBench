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
 int /*<<< orphan*/  bcopy (void*,void*,size_t const) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ const stage_offset ; 
 scalar_t__ const staging_end ; 

ssize_t
efi_copyout(const vm_offset_t src, void *dest, const size_t len)
{

	/* XXX: Callers do not check for failure. */
	if (src + stage_offset + len > staging_end) {
		errno = ENOMEM;
		return (-1);
	}
	bcopy((void *)(src + stage_offset), dest, len);
	return (len);
}