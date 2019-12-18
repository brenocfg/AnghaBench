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
struct TYPE_3__ {int /*<<< orphan*/  header; int /*<<< orphan*/  defaultBar; int /*<<< orphan*/  items; int /*<<< orphan*/  eventHandlerState; } ;
typedef  TYPE_1__ Panel ;

/* Variables and functions */
 int /*<<< orphan*/  FunctionBar_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RichString_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vector_delete (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void Panel_done(Panel* this) {
   assert (this != NULL);
   free(this->eventHandlerState);
   Vector_delete(this->items);
   FunctionBar_delete(this->defaultBar);
   RichString_end(this->header);
}