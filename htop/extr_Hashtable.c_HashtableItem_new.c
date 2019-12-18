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
struct TYPE_4__ {unsigned int key; int /*<<< orphan*/ * next; void* value; } ;
typedef  TYPE_1__ HashtableItem ;

/* Variables and functions */
 TYPE_1__* xMalloc (int) ; 

__attribute__((used)) static HashtableItem* HashtableItem_new(unsigned int key, void* value) {
   HashtableItem* this;
   
   this = xMalloc(sizeof(HashtableItem));
   this->key = key;
   this->value = value;
   this->next = NULL;
   return this;
}