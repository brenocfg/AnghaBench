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
struct TYPE_5__ {int items; int /*<<< orphan*/ ** array; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ Vector ;
typedef  int /*<<< orphan*/  Object ;

/* Variables and functions */
 int Object_isA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Vector_checkArraySize (TYPE_1__*) ; 
 int Vector_isConsistent (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

void Vector_insert(Vector* this, int idx, void* data_) {
   Object* data = data_;
   assert(idx >= 0);
   assert(Object_isA(data, this->type));
   assert(Vector_isConsistent(this));

   if (idx > this->items) {
      idx = this->items;
   }
   
   Vector_checkArraySize(this);
   //assert(this->array[this->items] == NULL);
   for (int i = this->items; i > idx; i--) {
      this->array[i] = this->array[i-1];
   }
   this->array[idx] = data;
   this->items++;
   assert(Vector_isConsistent(this));
}