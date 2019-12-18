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

/* Variables and functions */
 double delta_t () ; 
 int /*<<< orphan*/  printf (char*,int,double,double) ; 

__attribute__((used)) static void
TN(int count)
{
	double dt;

	dt = delta_t();
	printf("%5d iter in %10.6f sec = %8.3f msec\n",
		count, dt, dt * 1000.0 / count);
}