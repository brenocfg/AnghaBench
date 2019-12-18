#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_mruby_middleware_sender_t {TYPE_8__* subreq; int /*<<< orphan*/  sending; } ;
struct TYPE_13__ {TYPE_2__* ctx; scalar_t__ sender; } ;
typedef  TYPE_5__ h2o_mruby_generator_t ;
struct TYPE_12__ {TYPE_5__* body; int /*<<< orphan*/ * response; } ;
struct TYPE_11__ {int /*<<< orphan*/  request; } ;
struct TYPE_14__ {TYPE_4__ shortcut; TYPE_3__ refs; } ;
struct TYPE_10__ {TYPE_1__* shared; } ;
struct TYPE_9__ {int /*<<< orphan*/  mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  dispose_subreq (TYPE_8__*) ; 
 int /*<<< orphan*/  h2o_doublebuffer_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mruby_sender_close_body (TYPE_5__*) ; 
 int /*<<< orphan*/  mrb_gc_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 

void do_sender_dispose(h2o_mruby_generator_t *generator)
{
    struct st_h2o_mruby_middleware_sender_t *sender = (void *)generator->sender;

    h2o_doublebuffer_dispose(&sender->sending);

    if (sender->subreq->shortcut.response != NULL) {
        assert(!mrb_nil_p(sender->subreq->refs.request));
        mrb_gc_unregister(generator->ctx->shared->mrb, sender->subreq->refs.request);
        sender->subreq->shortcut.response = NULL;
    }

    assert(sender->subreq->shortcut.body == generator);
    sender->subreq->shortcut.body = NULL;

    dispose_subreq(sender->subreq);
    sender->subreq = NULL;

    h2o_mruby_sender_close_body(generator);
}