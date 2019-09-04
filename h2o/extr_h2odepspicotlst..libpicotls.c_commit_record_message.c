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
typedef  void* uint8_t ;
struct TYPE_4__ {TYPE_2__* buf; TYPE_3__* enc; } ;
struct st_ptls_record_message_emitter_t {int rec_start; TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  ptls_message_emitter_t ;
struct TYPE_6__ {int /*<<< orphan*/ * aead; } ;
struct TYPE_5__ {int off; void** base; } ;

/* Variables and functions */
 size_t PTLS_MAX_PLAINTEXT_RECORD_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int buffer_encrypt_record (TYPE_2__*,int,TYPE_3__*) ; 

__attribute__((used)) static int commit_record_message(ptls_message_emitter_t *_self)
{
    struct st_ptls_record_message_emitter_t *self = (void *)_self;
    int ret;

    if (self->super.enc->aead != NULL) {
        ret = buffer_encrypt_record(self->super.buf, self->rec_start, self->super.enc);
    } else {
        /* TODO allow CH,SH,HRR above 16KB */
        size_t sz = self->super.buf->off - self->rec_start - 5;
        assert(sz <= PTLS_MAX_PLAINTEXT_RECORD_SIZE);
        self->super.buf->base[self->rec_start + 3] = (uint8_t)(sz >> 8);
        self->super.buf->base[self->rec_start + 4] = (uint8_t)(sz);
        ret = 0;
    }

    return ret;
}