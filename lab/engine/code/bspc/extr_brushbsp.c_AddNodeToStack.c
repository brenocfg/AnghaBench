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
struct TYPE_5__ {struct TYPE_5__* next; } ;
typedef  TYPE_1__ node_t ;

/* Variables and functions */
 int /*<<< orphan*/  ThreadLock () ; 
 int /*<<< orphan*/  ThreadSemaphoreIncrease (int) ; 
 int /*<<< orphan*/  ThreadUnlock () ; 
 TYPE_1__* firstnode ; 
 TYPE_1__* lastnode ; 
 int /*<<< orphan*/  nodelistsize ; 

void AddNodeToStack(node_t *node)
{
	ThreadLock();

	node->next = firstnode;
	firstnode = node;
	if (!lastnode) lastnode = node;
	nodelistsize++;

	ThreadUnlock();
	//
	ThreadSemaphoreIncrease(1);
}