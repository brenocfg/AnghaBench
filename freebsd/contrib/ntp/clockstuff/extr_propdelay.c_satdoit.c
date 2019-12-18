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
 int /*<<< orphan*/  printf (char*,char*,double) ; 
 int /*<<< orphan*/  satfinddelay (double,double,double,double,double*) ; 

__attribute__((used)) static void
satdoit(
	double lat1,
	double long1,
	double lat2,
	double long2,
	double lat3,
	double long3,
	char *str
	)
{
	double up_delay,down_delay;

	satfinddelay(lat1, long1, lat2, long2, &up_delay);
	satfinddelay(lat3, long3, lat2, long2, &down_delay);

	printf("%s, delay %g seconds\n", str, up_delay + down_delay);
}