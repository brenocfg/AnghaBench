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
struct TYPE_4__ {int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 unsigned int NELEMS (TYPE_1__**) ; 
 TYPE_1__** arena ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* first ; 
 int /*<<< orphan*/ * freeblocks ; 

void deallocate(unsigned a) {
	assert(a < NELEMS(arena));
	arena[a]->next = freeblocks;
	freeblocks = first[a].next;
	first[a].next = NULL;
	arena[a] = &first[a];
}