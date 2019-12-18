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
struct TYPE_2__ {scalar_t__ when; } ;

/* Variables and functions */
 TYPE_1__* tims ; 

__attribute__((used)) static int
tim_cmp(const void *p1, const void *p2)
{
	int t1 = *(const int *)p1;
	int t2 = *(const int *)p2;

	return tims[t1].when < tims[t2].when ? -1
	     : tims[t1].when > tims[t2].when ? +1
	     :                        		  0;
}