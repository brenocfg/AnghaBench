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
struct os_tm {int dummy; } ;
typedef  int /*<<< orphan*/  os_time_t ;

/* Variables and functions */

int os_gmtime(os_time_t t, struct os_tm *tm)
{
	return -1;
}