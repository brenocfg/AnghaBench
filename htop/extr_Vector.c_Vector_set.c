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
struct TYPE_5__ {int items; int /*<<< orphan*/ ** array; scalar_t__ owner; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ Vector ;
typedef  int /*<<< orphan*/  Object ;

/* Variables and functions */
 int /*<<< orphan*/  Object_delete (int /*<<< orphan*/ *) ; 
 int Object_isA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vector_checkArraySize (TYPE_1__*) ; 
 int Vector_isConsistent (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

void Vector_set(Vector* this, int idx, void* data_) {
   Object* data = data_;
   assert(idx >= 0);
   assert(Object_isA((Object*)data, this->type));
   assert(Vector_isConsistent(this));

   Vector_checkArraySize(this);
   if (idx >= this->items) {
      this->items = idx+1;
   } else {
      if (this->owner) {
         Object* removed = this->array[idx];
         assert (removed != NULL);
         if (this->owner) {
            Object_delete(removed);
         }
      }
   }
   this->array[idx] = data;
   assert(Vector_isConsistent(this));
}