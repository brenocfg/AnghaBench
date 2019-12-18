#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int selected; int /*<<< orphan*/  items; } ;
typedef  TYPE_1__ Panel ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_SET_SELECTED ; 
 int /*<<< orphan*/  Panel_eventHandler (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ Panel_eventHandlerFn (TYPE_1__*) ; 
 int Vector_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void Panel_setSelected(Panel* this, int selected) {
   assert (this != NULL);

   int size = Vector_size(this->items);
   if (selected >= size) {
      selected = size - 1;
   }
   if (selected < 0)
      selected = 0;
   this->selected = selected;
   if (Panel_eventHandlerFn(this)) {
      Panel_eventHandler(this, EVENT_SET_SELECTED);
   }
}