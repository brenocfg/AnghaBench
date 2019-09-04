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
typedef  int /*<<< orphan*/  node_t ;
struct TYPE_2__ {int /*<<< orphan*/  numareas; int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_CreateAreas_r (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Log_Write (char*,...) ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 
 TYPE_1__ tmpaasworld ; 

void AAS_CreateAreas(node_t *node)
{
	Log_Write("AAS_CreateAreas\r\n");
	qprintf("%6d areas created", 0);
	tmpaasworld.nodes = AAS_CreateAreas_r(node);
	qprintf("\n");
	Log_Write("%6d areas created\r\n", tmpaasworld.numareas);
}