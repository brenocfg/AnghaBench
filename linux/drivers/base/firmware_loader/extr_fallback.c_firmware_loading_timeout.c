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
 long HZ ; 
 long MAX_JIFFY_OFFSET ; 
 long __firmware_loading_timeout () ; 

__attribute__((used)) static long firmware_loading_timeout(void)
{
	return __firmware_loading_timeout() > 0 ?
		__firmware_loading_timeout() * HZ : MAX_JIFFY_OFFSET;
}