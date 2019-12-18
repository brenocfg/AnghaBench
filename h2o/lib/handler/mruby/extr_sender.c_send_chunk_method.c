#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  inflight; } ;
struct TYPE_10__ {scalar_t__ bytes_left; int /*<<< orphan*/  final_sent; } ;
struct st_h2o_mruby_callback_sender_t {TYPE_5__* receiving; TYPE_4__ sending; TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;
struct TYPE_11__ {scalar_t__ sender; } ;
typedef  TYPE_2__ h2o_mruby_generator_t ;
struct TYPE_14__ {int /*<<< orphan*/ * base; } ;
struct TYPE_13__ {scalar_t__ bytes; scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_RUNTIME_ERROR ; 
 scalar_t__ SIZE_MAX ; 
 int /*<<< orphan*/  check_precond (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_7__ h2o_buffer_try_reserve (TYPE_5__**,scalar_t__) ; 
 TYPE_2__* h2o_mruby_get_generator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_mruby_sender_do_send_buffer (TYPE_2__*,TYPE_4__*,TYPE_5__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,scalar_t__) ; 
 int /*<<< orphan*/  mrb_exc_new_str_lit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_exc_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,char const**,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static mrb_value send_chunk_method(mrb_state *mrb, mrb_value self)
{
    const char *s;
    mrb_int len;
    mrb_value gen;

    /* parse args */
    mrb_get_args(mrb, "so", &s, &len, &gen);

    h2o_mruby_generator_t *generator = h2o_mruby_get_generator(mrb, gen);

    { /* precond check */
        mrb_value exc = check_precond(mrb, generator);
        if (!mrb_nil_p(exc))
            mrb_exc_raise(mrb, exc);
    }

    /* append to send buffer, and send out immediately if necessary */
    if (len != 0) {
        struct st_h2o_mruby_callback_sender_t *sender = (void *)generator->sender;
        if (sender->super.bytes_left != SIZE_MAX && sender->super.bytes_left < len)
            len = sender->super.bytes_left; /* trim data too long */
        if (len != 0) {
            if ((h2o_buffer_try_reserve(&sender->receiving, len)).base == NULL) {
                mrb_value exc = mrb_exc_new_str_lit(mrb, E_RUNTIME_ERROR, "failed to allocate memory");
                mrb_exc_raise(mrb, exc);
            }
            memcpy(sender->receiving->bytes + sender->receiving->size, s, len);
            sender->receiving->size += len;
            if (!sender->super.final_sent && !sender->sending.inflight)
                h2o_mruby_sender_do_send_buffer(generator, &sender->sending, &sender->receiving, 0);
        }
    }

    return mrb_nil_value();
}