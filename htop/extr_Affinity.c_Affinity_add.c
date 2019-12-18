#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int used; int size; int* cpus; } ;
typedef  TYPE_1__ Affinity ;

/* Variables and functions */
 int* xRealloc (int*,int) ; 

void Affinity_add(Affinity* this, int id) {
   if (this->used == this->size) {
      this->size *= 2;
      this->cpus = xRealloc(this->cpus, sizeof(int) * this->size);
   }
   this->cpus[this->used] = id;
   this->used++;
}