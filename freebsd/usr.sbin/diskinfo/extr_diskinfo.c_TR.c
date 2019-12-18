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
 int /*<<< orphan*/  printf (char*,double,double,double) ; 

__attribute__((used)) static void
TR(double count)
{
	double dt;

	dt = delta_t();
	printf("%8.0f kbytes in %10.6f sec = %8.0f kbytes/sec\n",
		count, dt, count / dt);
}