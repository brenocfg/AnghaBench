#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* classname; int /*<<< orphan*/  neverFree; } ;
typedef  TYPE_1__ gentity_t ;
struct TYPE_5__ {TYPE_1__** bodyQue; scalar_t__ bodyQueIndex; } ;

/* Variables and functions */
 int BODY_QUEUE_SIZE ; 
 TYPE_1__* G_Spawn () ; 
 TYPE_2__ level ; 
 int /*<<< orphan*/  qtrue ; 

void InitBodyQue (void) {
	int		i;
	gentity_t	*ent;

	level.bodyQueIndex = 0;
	for (i=0; i<BODY_QUEUE_SIZE ; i++) {
		ent = G_Spawn();
		ent->classname = "bodyque";
		ent->neverFree = qtrue;
		level.bodyQue[i] = ent;
	}
}