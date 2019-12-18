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
struct TYPE_5__ {int items; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ Vector ;
typedef  int /*<<< orphan*/  Object ;

/* Variables and functions */
 int Object_isA (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int Vector_isConsistent (TYPE_1__*) ; 
 int /*<<< orphan*/  Vector_set (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

void Vector_add(Vector* this, void* data_) {
   Object* data = data_;
   assert(Object_isA((Object*)data, this->type));
   assert(Vector_isConsistent(this));
   int i = this->items;
   Vector_set(this, this->items, data);
   assert(this->items == i+1); (void)(i);
   assert(Vector_isConsistent(this));
}