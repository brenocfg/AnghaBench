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
struct TYPE_2__ {double* cp_time; } ;

/* Variables and functions */
 int CPUSTATES ; 
 TYPE_1__ cur ; 
 int /*<<< orphan*/  printf (char*,double) ; 
 double rint (int) ; 

__attribute__((used)) static void
cpustats(void)
{
	int state;
	double cptime;

	cptime = 0.0;

	for (state = 0; state < CPUSTATES; ++state)
		cptime += cur.cp_time[state];
	for (state = 0; state < CPUSTATES; ++state)
		printf(" %2.0f",
		       rint(100. * cur.cp_time[state] / (cptime ? cptime : 1)));
}