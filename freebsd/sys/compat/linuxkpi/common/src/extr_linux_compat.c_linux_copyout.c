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
 int EFAULT ; 
 int copyout (void const*,void*,size_t) ; 
 scalar_t__ linux_remap_address (void**,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 

int
linux_copyout(const void *kaddr, void *uaddr, size_t len)
{
	if (linux_remap_address(&uaddr, len)) {
		if (uaddr == NULL)
			return (-EFAULT);
		memcpy(uaddr, kaddr, len);
		return (0);
	}
	return (-copyout(kaddr, uaddr, len));
}