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
typedef  unsigned long u64 ;

/* Variables and functions */
 unsigned long I3200_ECCERRLOG_SYNDROME_BITS ; 
 unsigned long I3200_ECCERRLOG_SYNDROME_SHIFT ; 

__attribute__((used)) static unsigned long eccerrlog_syndrome(u64 log)
{
	return (log & I3200_ECCERRLOG_SYNDROME_BITS) >>
		I3200_ECCERRLOG_SYNDROME_SHIFT;
}