#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  quicly_stream_t ;
struct TYPE_3__ {size_t off; scalar_t__ base; } ;
typedef  TYPE_1__ ptls_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,size_t) ; 
 int /*<<< orphan*/  quicly_stream_sync_recvbuf (int /*<<< orphan*/ *,size_t) ; 

void quicly_recvbuf_shift(quicly_stream_t *stream, ptls_buffer_t *rb, size_t delta)
{
    assert(delta <= rb->off);
    rb->off -= delta;
    memmove(rb->base, rb->base + delta, rb->off);

    quicly_stream_sync_recvbuf(stream, delta);
}