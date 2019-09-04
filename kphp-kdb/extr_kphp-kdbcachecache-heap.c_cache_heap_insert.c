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
struct TYPE_4__ {int size; int max_size; scalar_t__ (* compare ) (void*,void*) ;void** H; } ;
typedef  TYPE_1__ cache_heap_t ;

/* Variables and functions */
 int /*<<< orphan*/  heap_sift (TYPE_1__*,void*,int) ; 
 scalar_t__ stub1 (void*,void*) ; 
 scalar_t__ stub2 (void*,void*) ; 

void cache_heap_insert (cache_heap_t *self, void *E) {
  if (self->size < self->max_size) {
    int i = ++(self->size);
    while (i > 1) {
      int j = i >> 1;
      if (self->compare (self->H[j], E) >= 0) {
        break;
      }
      self->H[i] = self->H[j];
      i = j;
    }
    self->H[i] = E;
  } else {
    if (self->compare (self->H[1], E) > 0) {
      heap_sift (self, E, 1);
    }
  }
}