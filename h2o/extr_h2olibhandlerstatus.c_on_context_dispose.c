#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_status_context_t {int /*<<< orphan*/  receiver; } ;
struct TYPE_5__ {size_t size; int /*<<< orphan*/ ** entries; } ;
struct st_h2o_root_status_handler_t {TYPE_1__ receivers; int /*<<< orphan*/  super; } ;
typedef  int /*<<< orphan*/  h2o_handler_t ;
struct TYPE_6__ {int /*<<< orphan*/  queue; } ;
typedef  TYPE_2__ h2o_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (struct st_h2o_status_context_t*) ; 
 struct st_h2o_status_context_t* h2o_context_get_handler_context (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_multithread_unregister_receiver (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ **,int /*<<< orphan*/ **,size_t) ; 

__attribute__((used)) static void on_context_dispose(h2o_handler_t *_self, h2o_context_t *ctx)
{
    struct st_h2o_root_status_handler_t *self = (void *)_self;
    struct st_h2o_status_context_t *status_ctx = h2o_context_get_handler_context(ctx, &self->super);
    size_t i;

    for (i = 0; i != self->receivers.size; ++i)
        if (self->receivers.entries[i] == &status_ctx->receiver)
            break;
    assert(i != self->receivers.size);
    memmove(self->receivers.entries + i + 1, self->receivers.entries + i, self->receivers.size - i - 1);
    --self->receivers.size;

    h2o_multithread_unregister_receiver(ctx->queue, &status_ctx->receiver);

    free(status_ctx);
}