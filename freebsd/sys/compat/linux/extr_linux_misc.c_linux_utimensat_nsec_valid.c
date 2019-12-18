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
typedef  int l_long ;

/* Variables and functions */
 int LINUX_UTIME_NOW ; 
 int LINUX_UTIME_OMIT ; 

__attribute__((used)) static int
linux_utimensat_nsec_valid(l_long nsec)
{

	if (nsec == LINUX_UTIME_OMIT || nsec == LINUX_UTIME_NOW)
		return (0);
	if (nsec >= 0 && nsec <= 999999999)
		return (0);
	return (1);
}