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
 int /*<<< orphan*/  AAS_PruneNodes_r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Log_Print (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Log_Write (char*) ; 
 int /*<<< orphan*/  c_numprunes ; 
 TYPE_1__ tmpaasworld ; 

void AAS_PruneNodes(void)
{
	Log_Write("AAS_PruneNodes\r\n");
	AAS_PruneNodes_r(tmpaasworld.nodes);
	Log_Print("%6d nodes pruned\r\n", c_numprunes);
}