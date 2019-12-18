#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int items; scalar_t__* array; scalar_t__ owner; } ;
typedef  TYPE_1__ Vector ;

/* Variables and functions */
 int /*<<< orphan*/  Object_delete (scalar_t__) ; 
 int /*<<< orphan*/  Vector_isConsistent (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void Vector_prune(Vector* this) {
   assert(Vector_isConsistent(this));
   if (this->owner) {
      for (int i = 0; i < this->items; i++)
         if (this->array[i]) {
            Object_delete(this->array[i]);
            //this->array[i] = NULL;
         }
   }
   this->items = 0;
}