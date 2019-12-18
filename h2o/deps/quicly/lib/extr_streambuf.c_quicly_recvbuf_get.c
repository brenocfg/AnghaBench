#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* ranges; } ;
struct TYPE_12__ {scalar_t__ data_off; TYPE_1__ received; } ;
struct TYPE_10__ {TYPE_5__ recvstate; } ;
typedef  TYPE_3__ quicly_stream_t ;
typedef  int /*<<< orphan*/  ptls_iovec_t ;
struct TYPE_11__ {size_t off; int /*<<< orphan*/  base; } ;
typedef  TYPE_4__ ptls_buffer_t ;
struct TYPE_9__ {scalar_t__ end; } ;

/* Variables and functions */
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ quicly_recvstate_transfer_complete (TYPE_5__*) ; 

ptls_iovec_t quicly_recvbuf_get(quicly_stream_t *stream, ptls_buffer_t *rb)
{
    size_t avail;

    if (quicly_recvstate_transfer_complete(&stream->recvstate)) {
        avail = rb->off;
    } else if (stream->recvstate.data_off < stream->recvstate.received.ranges[0].end) {
        avail = stream->recvstate.received.ranges[0].end - stream->recvstate.data_off;
    } else {
        avail = 0;
    }

    return ptls_iovec_init(rb->base, avail);
}