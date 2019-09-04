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
struct TYPE_4__ {int size; void** H; } ;
typedef  TYPE_1__ cache_heap_t ;

/* Variables and functions */
 int /*<<< orphan*/  heap_sift (TYPE_1__*,void*,int) ; 

int cache_heap_sort (cache_heap_t *self) {
  int r = self->size;
  while (self->size > 1) {
    void *E = self->H[1];
    heap_sift (self, self->H[(self->size)--], 1);
    self->H[self->size+1] = E;
  }
  self->size = 0;
  return r;
}