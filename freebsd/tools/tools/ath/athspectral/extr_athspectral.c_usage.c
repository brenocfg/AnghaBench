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
 int /*<<< orphan*/  printf (char*,...) ; 

void
usage(const char *progname)
{
	printf("Usage:\n");
	printf("\t%s: [-i <interface>] <cmd> (<arg>)\n", progname);
	printf("\t%s: [-h]\n", progname);
	printf("\n");
	printf("Valid commands:\n");
	printf("\tget:\t\tGet current spectral parameters\n");
	printf("\tset <param> <value>:\t\tSet spectral parameter\n");
	printf("\tstart: Start spectral scan\n");
	printf("\tstop: Stop spectral scan\n");
	printf("\tenable_at_reset <0|1>: enable reporting upon channel reset\n");
}