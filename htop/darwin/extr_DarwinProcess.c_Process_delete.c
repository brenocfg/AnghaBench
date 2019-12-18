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
struct TYPE_3__ {int /*<<< orphan*/  super; } ;
typedef  int /*<<< orphan*/  Object ;
typedef  TYPE_1__ DarwinProcess ;

/* Variables and functions */
 int /*<<< orphan*/  Process_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void Process_delete(Object* cast) {
   DarwinProcess* this = (DarwinProcess*) cast;
   Process_done(&this->super);
   // free platform-specific fields here
   free(this);
}