#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct value_buffer {scalar_t__ wptr; scalar_t__ s; scalar_t__ n474; TYPE_1__* c; } ;
struct TYPE_2__ {int /*<<< orphan*/  Out; } ;

/* Variables and functions */
 int /*<<< orphan*/  advance_write_ptr (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ get_write_ptr (int /*<<< orphan*/ *,int) ; 

int value_buffer_flush (struct value_buffer *B) {
  if (B->wptr >= B->s) {
    advance_write_ptr (&B->c->Out, B->wptr - (B->s - B->n474));
    B->wptr = get_write_ptr (&B->c->Out, 512);
    if (!B->wptr) return 0;
    B->s = B->wptr + B->n474;
  }
  return 1;
}