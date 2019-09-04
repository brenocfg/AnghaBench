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
struct TYPE_2__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_GravitationalSubdivision_r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Log_Write (char*,...) ; 
 scalar_t__ numgravitationalsubdivisions ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 
 TYPE_1__ tmpaasworld ; 

void AAS_GravitationalSubdivision(void)
{
	Log_Write("AAS_GravitationalSubdivision\r\n");
	numgravitationalsubdivisions = 0;
	qprintf("%6i gravitational subdivisions", numgravitationalsubdivisions);
	//start with the head node
	AAS_GravitationalSubdivision_r(tmpaasworld.nodes);
	qprintf("\n");
	Log_Write("%6i gravitational subdivisions\r\n", numgravitationalsubdivisions);
}