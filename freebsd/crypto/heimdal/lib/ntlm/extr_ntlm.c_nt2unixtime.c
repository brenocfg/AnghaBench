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
typedef  int uint64_t ;
typedef  scalar_t__ time_t ;

/* Variables and functions */
 scalar_t__ NTTIME_EPOCH ; 

__attribute__((used)) static time_t
nt2unixtime(uint64_t t)
{
    t = ((t - (uint64_t)NTTIME_EPOCH) / (uint64_t)10000000);
    if (t > (((uint64_t)(time_t)(~(uint64_t)0)) >> 1))
	return 0;
    return (time_t)t;
}