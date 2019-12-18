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
 int LINUX_WCONTINUED ; 
 int LINUX_WEXITED ; 
 int LINUX_WNOHANG ; 
 int LINUX_WNOWAIT ; 
 int LINUX_WUNTRACED ; 
 int WCONTINUED ; 
 int WEXITED ; 
 int WLINUXCLONE ; 
 int WNOHANG ; 
 int WNOWAIT ; 
 int WUNTRACED ; 
 int __WCLONE ; 

void
linux_to_bsd_waitopts(int options, int *bsdopts)
{

	if (options & LINUX_WNOHANG)
		*bsdopts |= WNOHANG;
	if (options & LINUX_WUNTRACED)
		*bsdopts |= WUNTRACED;
	if (options & LINUX_WEXITED)
		*bsdopts |= WEXITED;
	if (options & LINUX_WCONTINUED)
		*bsdopts |= WCONTINUED;
	if (options & LINUX_WNOWAIT)
		*bsdopts |= WNOWAIT;

	if (options & __WCLONE)
		*bsdopts |= WLINUXCLONE;
}