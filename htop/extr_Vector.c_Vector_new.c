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
struct TYPE_4__ {int growthRate; int arraySize; int owner; int /*<<< orphan*/ * type; scalar_t__ items; int /*<<< orphan*/ ** array; } ;
typedef  TYPE_1__ Vector ;
typedef  int /*<<< orphan*/  ObjectClass ;
typedef  int /*<<< orphan*/  Object ;

/* Variables and functions */
 int DEFAULT_SIZE ; 
 scalar_t__ xCalloc (int,int) ; 
 TYPE_1__* xMalloc (int) ; 

Vector* Vector_new(ObjectClass* type, bool owner, int size) {
   Vector* this;

   if (size == DEFAULT_SIZE)
      size = 10;
   this = xMalloc(sizeof(Vector));
   this->growthRate = size;
   this->array = (Object**) xCalloc(size, sizeof(Object*));
   this->arraySize = size;
   this->items = 0;
   this->type = type;
   this->owner = owner;
   return this;
}