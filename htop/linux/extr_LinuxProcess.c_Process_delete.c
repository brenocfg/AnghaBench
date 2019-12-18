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
struct TYPE_3__ {struct TYPE_3__* ttyDevice; struct TYPE_3__* cgroup; } ;
typedef  int /*<<< orphan*/  Process ;
typedef  int /*<<< orphan*/  Object ;
typedef  TYPE_1__ LinuxProcess ;

/* Variables and functions */
 int /*<<< orphan*/  Process_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void Process_delete(Object* cast) {
   LinuxProcess* this = (LinuxProcess*) cast;
   Process_done((Process*)cast);
#ifdef HAVE_CGROUP
   free(this->cgroup);
#endif
   free(this->ttyDevice);
   free(this);
}