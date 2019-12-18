#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* timer_t ;
struct TYPE_3__ {int /*<<< orphan*/  oshandle; } ;

/* Variables and functions */
 int __sys_ktimer_getoverrun (int /*<<< orphan*/ ) ; 

int
__timer_getoverrun(timer_t timerid)
{

	return __sys_ktimer_getoverrun(timerid->oshandle);
}