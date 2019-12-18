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
 int /*<<< orphan*/  CPUSCALE ; 
 int CPUSTATES ; 
 int /*<<< orphan*/  INSET ; 
 TYPE_1__ cur_dev ; 
 int /*<<< orphan*/  histogram (double,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wnd ; 

__attribute__((used)) static void
stat1(int row, int o)
{
	int i;
	double dtime;

	dtime = 0.0;
	for (i = 0; i < CPUSTATES; i++)
		dtime += cur_dev.cp_time[i];
	if (dtime == 0.0)
		dtime = 1.0;
	wmove(wnd, row, INSET);
#define CPUSCALE	0.5
	histogram(100.0 * cur_dev.cp_time[o] / dtime, 50, CPUSCALE);
}