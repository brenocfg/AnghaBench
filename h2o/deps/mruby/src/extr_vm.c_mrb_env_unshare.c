#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct REnv {int /*<<< orphan*/ * stack; TYPE_1__* cxt; } ;
struct RBasic {int dummy; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_9__ {TYPE_1__* c; } ;
typedef  TYPE_3__ mrb_state ;
struct TYPE_8__ {struct REnv* env; } ;
struct TYPE_7__ {TYPE_2__* cibase; } ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_ENV_STACK_LEN (struct REnv*) ; 
 int /*<<< orphan*/  MRB_ENV_STACK_SHARED_P (struct REnv*) ; 
 int /*<<< orphan*/  MRB_ENV_UNSHARE_STACK (struct REnv*) ; 
 scalar_t__ mrb_malloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/  mrb_write_barrier (TYPE_3__*,struct RBasic*) ; 
 int /*<<< orphan*/  stack_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

void
mrb_env_unshare(mrb_state *mrb, struct REnv *e)
{
  if (e == NULL) return;
  else {
    size_t len = (size_t)MRB_ENV_STACK_LEN(e);
    mrb_value *p;

    if (!MRB_ENV_STACK_SHARED_P(e)) return;
    if (e->cxt != mrb->c) return;
    if (e == mrb->c->cibase->env) return; /* for mirb */
    p = (mrb_value *)mrb_malloc(mrb, sizeof(mrb_value)*len);
    if (len > 0) {
      stack_copy(p, e->stack, len);
    }
    e->stack = p;
    MRB_ENV_UNSHARE_STACK(e);
    mrb_write_barrier(mrb, (struct RBasic *)e);
  }
}