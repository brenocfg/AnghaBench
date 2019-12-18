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
struct TYPE_4__ {TYPE_1__* buf; } ;
struct st_ptls_raw_message_emitter_t {TYPE_2__ super; int /*<<< orphan*/  start_off; } ;
typedef  int /*<<< orphan*/  ptls_message_emitter_t ;
struct TYPE_3__ {int /*<<< orphan*/  off; } ;

/* Variables and functions */

__attribute__((used)) static int begin_raw_message(ptls_message_emitter_t *_self)
{
    struct st_ptls_raw_message_emitter_t *self = (void *)_self;

    self->start_off = self->super.buf->off;
    return 0;
}