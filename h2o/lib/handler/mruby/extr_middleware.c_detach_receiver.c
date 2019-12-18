#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_mruby_subreq_t {TYPE_2__* ctx; int /*<<< orphan*/  receiver; } ;
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_4__ {TYPE_1__* shared; } ;
struct TYPE_3__ {int /*<<< orphan*/  mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  mrb_gc_protect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gc_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static mrb_value detach_receiver(struct st_mruby_subreq_t *subreq)
{
    mrb_value receiver = subreq->receiver;
    assert(!mrb_nil_p(receiver));
    subreq->receiver = mrb_nil_value();
    mrb_gc_unregister(subreq->ctx->shared->mrb, receiver);
    mrb_gc_protect(subreq->ctx->shared->mrb, receiver);
    return receiver;
}