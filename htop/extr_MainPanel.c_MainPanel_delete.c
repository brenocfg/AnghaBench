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
struct TYPE_3__ {struct TYPE_3__* keys; int /*<<< orphan*/  inc; } ;
typedef  int /*<<< orphan*/  Panel ;
typedef  int /*<<< orphan*/  Object ;
typedef  TYPE_1__ MainPanel ;

/* Variables and functions */
 int /*<<< orphan*/  IncSet_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Panel_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void MainPanel_delete(Object* object) {
   Panel* super = (Panel*) object;
   MainPanel* this = (MainPanel*) object;
   Panel_done(super);
   IncSet_delete(this->inc);
   free(this->keys);
   free(this);
}