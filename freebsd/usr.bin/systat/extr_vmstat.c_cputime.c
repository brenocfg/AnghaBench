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
struct TYPE_2__ {double* time; } ;

/* Variables and functions */
 int CPUSTATES ; 
 TYPE_1__ s ; 

__attribute__((used)) static float
cputime(int indx)
{
	double lt;
	int i;

	lt = 0;
	for (i = 0; i < CPUSTATES; i++)
		lt += s.time[i];
	if (lt == 0.0)
		lt = 1.0;
	return (s.time[indx] * 100.0 / lt);
}