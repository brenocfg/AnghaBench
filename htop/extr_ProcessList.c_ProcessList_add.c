#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pid; } ;
struct TYPE_8__ {int /*<<< orphan*/  processes; int /*<<< orphan*/  processTable; } ;
typedef  TYPE_1__ ProcessList ;
typedef  TYPE_2__ Process ;

/* Variables and functions */
 scalar_t__ Hashtable_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Hashtable_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Hashtable_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Process_pidCompare ; 
 int /*<<< orphan*/  Vector_add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ Vector_count (int /*<<< orphan*/ ) ; 
 int Vector_indexOf (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

void ProcessList_add(ProcessList* this, Process* p) {
   assert(Vector_indexOf(this->processes, p, Process_pidCompare) == -1);
   assert(Hashtable_get(this->processTable, p->pid) == NULL);
   
   Vector_add(this->processes, p);
   Hashtable_put(this->processTable, p->pid, p);
   
   assert(Vector_indexOf(this->processes, p, Process_pidCompare) != -1);
   assert(Hashtable_get(this->processTable, p->pid) != NULL);
   assert(Hashtable_count(this->processTable) == Vector_count(this->processes));
}