#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* ee_rdEdgesPower; } ;
struct TYPE_3__ {scalar_t__ rdEdge; int twice_rdEdgePower; } ;
typedef  TYPE_1__ RD_EDGES_POWER ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t NUM_EDGES ; 
 size_t curctl ; 
 TYPE_2__ eeprom ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
printEdgePower(FILE *fd, int edge)
{
	const RD_EDGES_POWER *pRdEdgePwrInfo =
	    &eeprom.ee_rdEdgesPower[curctl*NUM_EDGES];

	if (pRdEdgePwrInfo[edge].rdEdge == 0)
		fprintf(fd, " -- ");
	else
                fprintf(fd, "%2d.%d",
		    pRdEdgePwrInfo[edge].twice_rdEdgePower / 2,
                    (pRdEdgePwrInfo[edge].twice_rdEdgePower % 2) * 5);
}