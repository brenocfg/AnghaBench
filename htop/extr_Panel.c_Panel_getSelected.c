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
struct TYPE_3__ {int /*<<< orphan*/  selected; int /*<<< orphan*/  items; } ;
typedef  TYPE_1__ Panel ;
typedef  int /*<<< orphan*/  Object ;

/* Variables and functions */
 int /*<<< orphan*/ * Vector_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Vector_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

Object* Panel_getSelected(Panel* this) {
   assert (this != NULL);
   if (Vector_size(this->items) > 0)
      return Vector_get(this->items, this->selected);
   else
      return NULL;
}