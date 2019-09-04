#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  inflight; } ;
struct TYPE_7__ {int /*<<< orphan*/  final_sent; } ;
struct st_h2o_mruby_http_sender_t {TYPE_5__ sending; TYPE_1__ super; } ;
struct TYPE_8__ {scalar_t__ sender; } ;
typedef  TYPE_2__ h2o_mruby_generator_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SEND_STATE_IN_PROGRESS ; 
 int /*<<< orphan*/  h2o_doublebuffer_prepare_empty (TYPE_5__*) ; 
 int /*<<< orphan*/  h2o_mruby_sender_do_send (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_shortcut_notify (TYPE_2__*) ; 

__attribute__((used)) static void do_sender_start(h2o_mruby_generator_t *generator)
{
    struct st_h2o_mruby_http_sender_t *sender = (void *)generator->sender;

    on_shortcut_notify(generator);

    if (!sender->super.final_sent && !sender->sending.inflight) {
        h2o_doublebuffer_prepare_empty(&sender->sending);
        h2o_mruby_sender_do_send(generator, NULL, 0, H2O_SEND_STATE_IN_PROGRESS);
    }
}