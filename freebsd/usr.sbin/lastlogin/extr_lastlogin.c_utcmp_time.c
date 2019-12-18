#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
struct TYPE_2__ {scalar_t__ tv_sec; } ;
struct utmpx {TYPE_1__ ut_tv; } ;

/* Variables and functions */
 int order ; 

__attribute__((used)) static int
utcmp_time(const void *u1, const void *u2)
{
	time_t t1, t2;

	t1 = ((const struct utmpx *)u1)->ut_tv.tv_sec;
	t2 = ((const struct utmpx *)u2)->ut_tv.tv_sec;
	return (t1 < t2 ? order : t1 > t2 ? -order : 0);
}