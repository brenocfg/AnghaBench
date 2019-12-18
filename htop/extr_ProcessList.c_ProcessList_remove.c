#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int pid; } ;
struct TYPE_7__ {int /*<<< orphan*/  processes; int /*<<< orphan*/  processTable; } ;
typedef  TYPE_1__ ProcessList ;
typedef  TYPE_2__ Process ;

/* Variables and functions */
 scalar_t__ Hashtable_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Hashtable_get (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_2__* Hashtable_remove (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  Process_pidCompare ; 
 scalar_t__ Vector_count (int /*<<< orphan*/ ) ; 
 int Vector_indexOf (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vector_remove (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 

void ProcessList_remove(ProcessList* this, Process* p) {
   assert(Vector_indexOf(this->processes, p, Process_pidCompare) != -1);
   assert(Hashtable_get(this->processTable, p->pid) != NULL);
   Process* pp = Hashtable_remove(this->processTable, p->pid);
   assert(pp == p); (void)pp;
   unsigned int pid = p->pid;
   int idx = Vector_indexOf(this->processes, p, Process_pidCompare);
   assert(idx != -1);
   if (idx >= 0) Vector_remove(this->processes, idx);
   assert(Hashtable_get(this->processTable, pid) == NULL); (void)pid;
   assert(Hashtable_count(this->processTable) == Vector_count(this->processes));
}