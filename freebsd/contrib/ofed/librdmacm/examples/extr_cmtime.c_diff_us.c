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
struct timeval {int tv_sec; float tv_usec; } ;

/* Variables and functions */

__attribute__((used)) static float diff_us(struct timeval *end, struct timeval *start)
{
	return (end->tv_sec - start->tv_sec) * 1000000. + (end->tv_usec - start->tv_usec);
}