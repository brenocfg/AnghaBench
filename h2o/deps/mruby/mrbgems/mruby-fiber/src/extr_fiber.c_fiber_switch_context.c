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
struct mrb_context {int /*<<< orphan*/  status; scalar_t__ fib; } ;
struct RBasic {int dummy; } ;
struct TYPE_4__ {struct mrb_context* c; } ;
typedef  TYPE_1__ mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_FIBER_RUNNING ; 
 int /*<<< orphan*/  mrb_write_barrier (TYPE_1__*,struct RBasic*) ; 

__attribute__((used)) static void
fiber_switch_context(mrb_state *mrb, struct mrb_context *c)
{
  if (mrb->c->fib) {
    mrb_write_barrier(mrb, (struct RBasic*)mrb->c->fib);
  }
  c->status = MRB_FIBER_RUNNING;
  mrb->c = c;
}