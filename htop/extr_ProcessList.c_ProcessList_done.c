#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  processes2; int /*<<< orphan*/  processes; int /*<<< orphan*/  processTable; int /*<<< orphan*/  topology; scalar_t__ topologyOk; } ;
typedef  TYPE_1__ ProcessList ;

/* Variables and functions */
 int /*<<< orphan*/  Hashtable_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vector_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwloc_topology_destroy (int /*<<< orphan*/ ) ; 

void ProcessList_done(ProcessList* this) {
#ifdef HAVE_LIBHWLOC
   if (this->topologyOk) {
      hwloc_topology_destroy(this->topology);
   }
#endif
   Hashtable_delete(this->processTable);
   Vector_delete(this->processes);
   Vector_delete(this->processes2);
}