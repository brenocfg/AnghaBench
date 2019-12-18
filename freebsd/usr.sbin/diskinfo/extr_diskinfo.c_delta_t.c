#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tv_usec; scalar_t__ tv_sec; } ;
struct TYPE_4__ {int tv_usec; scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  gettimeofday (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__ tv1 ; 
 TYPE_1__ tv2 ; 

__attribute__((used)) static double
delta_t(void)
{
	double dt;

	gettimeofday(&tv2, NULL);
	dt = (tv2.tv_usec - tv1.tv_usec) / 1e6;
	dt += (tv2.tv_sec - tv1.tv_sec);

	return (dt);
}