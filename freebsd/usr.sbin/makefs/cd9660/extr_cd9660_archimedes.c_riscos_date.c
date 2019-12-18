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
typedef  int u_int64_t ;
typedef  scalar_t__ time_t ;

/* Variables and functions */

__attribute__((used)) static u_int64_t
riscos_date(time_t unixtime)
{
	u_int64_t base;

	base = 31536000ULL * 70 + 86400 * 17;
	return (((u_int64_t)unixtime) + base)*100;
}