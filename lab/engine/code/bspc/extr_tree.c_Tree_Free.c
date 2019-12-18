#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  headnode; } ;
typedef  TYPE_1__ tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (TYPE_1__*) ; 
 int /*<<< orphan*/  Log_Print (char*) ; 
 scalar_t__ MemorySize (TYPE_1__*) ; 
 int /*<<< orphan*/  PrintMemorySize (scalar_t__) ; 
 int /*<<< orphan*/  Tree_FreePortals_r (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Tree_Free_r (int /*<<< orphan*/ ) ; 
 scalar_t__ freedtreemem ; 

void Tree_Free(tree_t *tree)
{
	//if no tree just return
	if (!tree) return;
	//
	freedtreemem = 0;
	//
	Tree_FreePortals_r(tree->headnode);
	Tree_Free_r(tree->headnode);
#ifdef ME
	freedtreemem += MemorySize(tree);
#endif //ME
	FreeMemory(tree);
#ifdef ME
	Log_Print("freed ");
	PrintMemorySize(freedtreemem);
	Log_Print(" of tree memory\n");
#endif //ME
}