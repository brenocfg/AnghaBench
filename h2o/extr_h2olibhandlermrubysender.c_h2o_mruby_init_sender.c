#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
struct TYPE_17__ {int /*<<< orphan*/ * exc; } ;
typedef  TYPE_4__ mrb_state ;
struct TYPE_18__ {int /*<<< orphan*/  proceed; } ;
typedef  TYPE_5__ h2o_mruby_sender_t ;
struct TYPE_14__ {int /*<<< orphan*/  proceed; } ;
struct TYPE_19__ {TYPE_1__ super; TYPE_5__* sender; TYPE_3__* ctx; } ;
typedef  TYPE_6__ h2o_mruby_generator_t ;
struct TYPE_16__ {TYPE_2__* shared; } ;
struct TYPE_15__ {TYPE_4__* mrb; } ;

/* Variables and functions */
 TYPE_5__* callback_sender_create (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* h2o_mruby_http_sender_create (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* h2o_mruby_middleware_sender_create (TYPE_6__*,int /*<<< orphan*/ ) ; 

int h2o_mruby_init_sender(h2o_mruby_generator_t *generator, mrb_value body)
{
    mrb_state *mrb = generator->ctx->shared->mrb;
    h2o_mruby_sender_t *sender;

#define TRY(func)                                                                                                                  \
    do {                                                                                                                           \
        sender = func(generator, body);                                                                                            \
        if (mrb->exc != NULL)                                                                                                      \
            return -1;                                                                                                             \
        if (sender != NULL)                                                                                                        \
            goto Found;                                                                                                            \
    } while (0)

    TRY(h2o_mruby_http_sender_create);
    TRY(h2o_mruby_middleware_sender_create);
    TRY(callback_sender_create);

#undef TRY

    return -1;

Found:
    generator->sender = sender;
    generator->super.proceed = sender->proceed;
    return 0;
}