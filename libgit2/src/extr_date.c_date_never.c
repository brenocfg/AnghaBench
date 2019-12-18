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
typedef  int /*<<< orphan*/  time_t ;
typedef  int tm ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (int*) ; 
 int /*<<< orphan*/  p_localtime_r (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void date_never(struct tm *tm, struct tm *now, int *num)
{
	time_t n = 0;
   GIT_UNUSED(now);
   GIT_UNUSED(num);
	p_localtime_r(&n, tm);
}