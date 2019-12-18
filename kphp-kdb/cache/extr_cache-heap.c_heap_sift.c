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
struct TYPE_3__ {int size; scalar_t__ (* compare ) (void*,void*) ;void** H; } ;
typedef  TYPE_1__ cache_heap_t ;

/* Variables and functions */
 scalar_t__ stub1 (void*,void*) ; 
 scalar_t__ stub2 (void*,void*) ; 

__attribute__((used)) static void heap_sift (cache_heap_t *self, void *E, int i) {
  while (1) {
    int j = i << 1;
    if (j > self->size) {
      break;
    }
    if (j < self->size && self->compare (self->H[j], self->H[j+1]) < 0) {
      j++;
    }
    if (self->compare (E, self->H[j]) >= 0) {
      break;
    }
    self->H[i] = self->H[j];
    i = j;
  }
  self->H[i] = E;
}