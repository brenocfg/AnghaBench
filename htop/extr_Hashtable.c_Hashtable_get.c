#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int size; TYPE_1__** buckets; } ;
struct TYPE_5__ {unsigned int key; void* value; struct TYPE_5__* next; } ;
typedef  TYPE_1__ HashtableItem ;
typedef  TYPE_2__ Hashtable ;

/* Variables and functions */
 int /*<<< orphan*/  Hashtable_isConsistent (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

inline void* Hashtable_get(Hashtable* this, unsigned int key) {
   unsigned int index = key % this->size;
   HashtableItem* bucketPtr = this->buckets[index];
   while (true) {
      if (bucketPtr == NULL) {
         assert(Hashtable_isConsistent(this));
         return NULL;
      } else if (bucketPtr->key == key) {
         assert(Hashtable_isConsistent(this));
         return bucketPtr->value;
      } else
         bucketPtr = bucketPtr->next;
   }
}