#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ node_t ;

/* Variables and functions */
 scalar_t__ GetNumThreads () ; 
 int /*<<< orphan*/  ThreadLock () ; 
 int /*<<< orphan*/  ThreadSemaphoreIncrease (scalar_t__) ; 
 int /*<<< orphan*/  ThreadSemaphoreWait () ; 
 int /*<<< orphan*/  ThreadUnlock () ; 
 TYPE_1__* firstnode ; 
 int /*<<< orphan*/ * lastnode ; 
 int /*<<< orphan*/  nodelistsize ; 
 scalar_t__ numwaiting ; 

node_t *NextNodeFromList(void)
{
	node_t *node;

	ThreadLock();
	numwaiting++;
	if (!firstnode)
	{
		if (numwaiting >= GetNumThreads()) ThreadSemaphoreIncrease(GetNumThreads());
	} //end if
	ThreadUnlock();

	ThreadSemaphoreWait();

	ThreadLock();

	numwaiting--;

	node = firstnode;
	if (firstnode)
	{
		firstnode = firstnode->next;
		nodelistsize--;
	} //end if
	if (!firstnode) lastnode = NULL;

	ThreadUnlock();

	return node;
}