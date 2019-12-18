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
typedef  long long uint64_t ;
typedef  long long time_t ;

/* Variables and functions */
 scalar_t__ NTTIME_EPOCH ; 

__attribute__((used)) static uint64_t
unix2nttime(time_t unix_time)
{
    long long wt;
    wt = unix_time * (uint64_t)10000000 + (uint64_t)NTTIME_EPOCH;
    return wt;
}