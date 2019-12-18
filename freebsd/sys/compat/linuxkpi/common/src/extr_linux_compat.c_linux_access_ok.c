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
 uintptr_t VM_MAXUSER_ADDRESS ; 

int
linux_access_ok(const void *uaddr, size_t len)
{
	uintptr_t saddr;
	uintptr_t eaddr;

	/* get start and end address */
	saddr = (uintptr_t)uaddr;
	eaddr = (uintptr_t)uaddr + len;

	/* verify addresses are valid for userspace */
	return ((saddr == eaddr) ||
	    (eaddr > saddr && eaddr <= VM_MAXUSER_ADDRESS));
}