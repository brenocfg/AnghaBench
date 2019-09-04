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
struct TYPE_3__ {TYPE_2__* buf; } ;
struct st_ptls_record_message_emitter_t {TYPE_1__ super; int /*<<< orphan*/  rec_start; } ;
typedef  int /*<<< orphan*/  ptls_message_emitter_t ;
struct TYPE_4__ {int /*<<< orphan*/  off; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_CONTENT_TYPE_HANDSHAKE ; 
 int /*<<< orphan*/  PTLS_RECORD_VERSION_MAJOR ; 
 int /*<<< orphan*/  PTLS_RECORD_VERSION_MINOR ; 
 int /*<<< orphan*/  ptls_buffer_push (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int begin_record_message(ptls_message_emitter_t *_self)
{
    struct st_ptls_record_message_emitter_t *self = (void *)_self;
    int ret;

    self->rec_start = self->super.buf->off;
    ptls_buffer_push(self->super.buf, PTLS_CONTENT_TYPE_HANDSHAKE, PTLS_RECORD_VERSION_MAJOR, PTLS_RECORD_VERSION_MINOR, 0, 0);
    ret = 0;
Exit:
    return ret;
}