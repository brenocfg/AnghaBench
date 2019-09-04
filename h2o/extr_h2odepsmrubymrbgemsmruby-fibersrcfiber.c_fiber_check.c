#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mrb_context {int dummy; } ;
struct RFiber {scalar_t__ tt; struct mrb_context* cxt; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  E_FIBER_ERROR ; 
 scalar_t__ MRB_TT_FIBER ; 
 struct RFiber* fiber_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_assert (int) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct mrb_context*
fiber_check(mrb_state *mrb, mrb_value fib)
{
  struct RFiber *f = fiber_ptr(fib);

  mrb_assert(f->tt == MRB_TT_FIBER);
  if (!f->cxt) {
    mrb_raise(mrb, E_FIBER_ERROR, "uninitialized Fiber");
  }
  return f->cxt;
}