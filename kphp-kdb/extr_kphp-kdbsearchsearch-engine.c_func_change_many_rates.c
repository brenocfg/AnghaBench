#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* h; int /*<<< orphan*/  filled; } ;
struct TYPE_5__ {int* b; int k; TYPE_3__ HII; } ;
typedef  TYPE_2__ ctx_change_many_rates_t ;
struct TYPE_4__ {int key; int value; } ;

/* Variables and functions */
 int /*<<< orphan*/  hashmap_int_int_get (TYPE_3__*,int,int*) ; 

__attribute__((used)) static void func_change_many_rates (void *ctx, int i) {
  ctx_change_many_rates_t *self = (ctx_change_many_rates_t *) ctx;
  self->b[self->k++] = i;
  if (self->k == 2) {
    int slot;
    if (self->b[0]) {
      if (!hashmap_int_int_get (&self->HII, self->b[0], &slot)) {
        self->HII.h[slot].key = self->b[0];
        self->HII.filled++;
      }
      self->HII.h[slot].value = self->b[1];
    }
    self->k = 0;
  }
}