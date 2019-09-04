#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct mrb_context {int /*<<< orphan*/  eidx; TYPE_2__* ci; TYPE_2__* cibase; TYPE_2__* ciend; } ;
typedef  int ptrdiff_t ;
struct TYPE_7__ {struct mrb_context* c; } ;
typedef  TYPE_1__ mrb_state ;
struct TYPE_8__ {int ridx; int /*<<< orphan*/  epos; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ mrb_callinfo ;

/* Variables and functions */
 scalar_t__ mrb_realloc (TYPE_1__*,TYPE_2__*,int) ; 

__attribute__((used)) static inline mrb_callinfo*
cipush(mrb_state *mrb)
{
  struct mrb_context *c = mrb->c;
  static const mrb_callinfo ci_zero = { 0 };
  mrb_callinfo *ci = c->ci;

  int ridx = ci->ridx;

  if (ci + 1 == c->ciend) {
    ptrdiff_t size = ci - c->cibase;

    c->cibase = (mrb_callinfo *)mrb_realloc(mrb, c->cibase, sizeof(mrb_callinfo)*size*2);
    c->ci = c->cibase + size;
    c->ciend = c->cibase + size * 2;
  }
  ci = ++c->ci;
  *ci = ci_zero;
  ci->epos = mrb->c->eidx;
  ci->ridx = ridx;

  return ci;
}