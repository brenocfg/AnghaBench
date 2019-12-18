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
struct TYPE_4__ {int items; int arraySize; int growthRate; int /*<<< orphan*/ ** array; } ;
typedef  TYPE_1__ Vector ;
typedef  int /*<<< orphan*/  Object ;

/* Variables and functions */
 int /*<<< orphan*/  Vector_isConsistent (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ xRealloc (int /*<<< orphan*/ **,int) ; 

__attribute__((used)) static void Vector_checkArraySize(Vector* this) {
   assert(Vector_isConsistent(this));
   if (this->items >= this->arraySize) {
      //int i;
      //i = this->arraySize;
      this->arraySize = this->items + this->growthRate;
      this->array = (Object**) xRealloc(this->array, sizeof(Object*) * this->arraySize);
      //for (; i < this->arraySize; i++)
      //   this->array[i] = NULL;
   }
   assert(Vector_isConsistent(this));
}