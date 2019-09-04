#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* buf; TYPE_3__* enc; } ;
struct st_ptls_raw_message_emitter_t {size_t start_off; size_t* epoch_offsets; TYPE_2__ super; } ;
typedef  int /*<<< orphan*/  ptls_message_emitter_t ;
struct TYPE_6__ {size_t epoch; } ;
struct TYPE_4__ {scalar_t__* base; size_t off; } ;

/* Variables and functions */
 scalar_t__ PTLS_HANDSHAKE_TYPE_CLIENT_HELLO ; 
 size_t SIZE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int commit_raw_message(ptls_message_emitter_t *_self)
{
    struct st_ptls_raw_message_emitter_t *self = (void *)_self;
    size_t epoch;

    /* epoch is the key epoch, with the only exception being 2nd CH generated after 0-RTT key */
    epoch = self->super.enc->epoch;
    if (epoch == 1 && self->super.buf->base[self->start_off] == PTLS_HANDSHAKE_TYPE_CLIENT_HELLO)
        epoch = 0;

    for (++epoch; epoch < 5; ++epoch) {
        assert(self->epoch_offsets[epoch] == self->start_off);
        self->epoch_offsets[epoch] = self->super.buf->off;
    }

    self->start_off = SIZE_MAX;

    return 0;
}