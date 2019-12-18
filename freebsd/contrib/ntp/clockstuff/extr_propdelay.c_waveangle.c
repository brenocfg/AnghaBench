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
 double EARTHRADIUS ; 
 double RADPERDEG ; 
 double atan (scalar_t__) ; 
 int debug ; 
 int /*<<< orphan*/  printf (char*,double,double,int,double) ; 
 double sin (double) ; 
 scalar_t__ tan (double) ; 

__attribute__((used)) static double
waveangle(
	double dg,
	double h,
	int n
	)
{
	double theta;
	double delta;

	theta = dg / (EARTHRADIUS * (double)(2 * n));
	delta = atan((h / (EARTHRADIUS * sin(theta))) + tan(theta/2)) - theta;
	if (debug >= 2)
	    printf("waveangle dist %g height %g hops %d angle %g\n",
		   dg, h, n, delta / RADPERDEG);
	return delta;
}