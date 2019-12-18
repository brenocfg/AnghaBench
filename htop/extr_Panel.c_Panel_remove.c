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
struct TYPE_3__ {int needsRedraw; scalar_t__ selected; int /*<<< orphan*/  items; } ;
typedef  TYPE_1__ Panel ;
typedef  int /*<<< orphan*/  Object ;

/* Variables and functions */
 int /*<<< orphan*/ * Vector_remove (int /*<<< orphan*/ ,int) ; 
 scalar_t__ Vector_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

Object* Panel_remove(Panel* this, int i) {
   assert (this != NULL);

   this->needsRedraw = true;
   Object* removed = Vector_remove(this->items, i);
   if (this->selected > 0 && this->selected >= Vector_size(this->items))
      this->selected--;
   return removed;
}