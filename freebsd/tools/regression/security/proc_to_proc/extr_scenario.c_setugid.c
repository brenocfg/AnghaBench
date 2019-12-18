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
 int ENOSYS ; 
 int __setugid (int) ; 
 int syscall (int,int) ; 

int
setugid(int flag)
{

#ifdef SETSUGID_SUPPORTED
	return (__setugid(flag));
#else
#ifdef SETSUGID_SUPPORTED_BUT_NO_LIBC_STUB
	return (syscall(374, flag));
#else
	return (ENOSYS);
#endif
#endif
}