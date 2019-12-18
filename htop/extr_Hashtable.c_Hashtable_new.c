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
struct TYPE_5__ {int size; int owner; int /*<<< orphan*/ ** buckets; scalar_t__ items; } ;
typedef  int /*<<< orphan*/  HashtableItem ;
typedef  TYPE_1__ Hashtable ;

/* Variables and functions */
 int /*<<< orphan*/  Hashtable_isConsistent (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ xCalloc (int,int) ; 
 TYPE_1__* xMalloc (int) ; 

Hashtable* Hashtable_new(int size, bool owner) {
   Hashtable* this;
   
   this = xMalloc(sizeof(Hashtable));
   this->items = 0;
   this->size = size;
   this->buckets = (HashtableItem**) xCalloc(size, sizeof(HashtableItem*));
   this->owner = owner;
   assert(Hashtable_isConsistent(this));
   return this;
}