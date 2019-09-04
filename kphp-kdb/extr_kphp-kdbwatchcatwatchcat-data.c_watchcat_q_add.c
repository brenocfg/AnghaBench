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
struct TYPE_4__ {int vn; struct TYPE_4__* parent; struct TYPE_4__* next; struct TYPE_4__* prev; } ;
typedef  TYPE_1__ watchcat ;

/* Variables and functions */

inline void watchcat_q_add (watchcat *f, watchcat *e) {
  watchcat *b = f->prev;

  e->next = f;
  f->prev = e;

  e->prev = b;
  b->next = e;

  e->parent = f;
  if (f->vn < 2000000000) {
    f->vn++;
  }
}