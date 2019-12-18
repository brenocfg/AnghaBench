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
 scalar_t__ geteuid () ; 
 scalar_t__ getuid () ; 

int
platform_privileged_uidswap(void)
{
#ifdef HAVE_CYGWIN
	/* uid 0 is not special on Cygwin so always try */
	return 1;
#else
	return (getuid() == 0 || geteuid() == 0);
#endif
}