#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int size; scalar_t__ owner; int /*<<< orphan*/  items; TYPE_1__** buckets; } ;
struct TYPE_6__ {unsigned int key; struct TYPE_6__* next; void* value; } ;
typedef  TYPE_1__ HashtableItem ;
typedef  TYPE_2__ Hashtable ;

/* Variables and functions */
 TYPE_1__* HashtableItem_new (unsigned int,void*) ; 
 int /*<<< orphan*/  Hashtable_isConsistent (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*) ; 

void Hashtable_put(Hashtable* this, unsigned int key, void* value) {
   unsigned int index = key % this->size;
   HashtableItem** bucketPtr = &(this->buckets[index]);
   while (true)
      if (*bucketPtr == NULL) {
         *bucketPtr = HashtableItem_new(key, value);
         this->items++;
         break;
      } else if ((*bucketPtr)->key == key) {
         if (this->owner)
            free((*bucketPtr)->value);
         (*bucketPtr)->value = value;
         break;
      } else
         bucketPtr = &((*bucketPtr)->next);
   assert(Hashtable_isConsistent(this));
}