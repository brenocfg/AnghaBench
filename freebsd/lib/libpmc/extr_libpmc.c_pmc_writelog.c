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
typedef  int /*<<< orphan*/  uint32_t ;
struct pmc_op_writelog {int /*<<< orphan*/  pm_userdata; } ;

/* Variables and functions */
 int PMC_CALL (int /*<<< orphan*/ ,struct pmc_op_writelog*) ; 
 int /*<<< orphan*/  WRITELOG ; 

int
pmc_writelog(uint32_t userdata)
{
	struct pmc_op_writelog wl;

	wl.pm_userdata = userdata;
	return (PMC_CALL(WRITELOG, &wl));
}