#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  bytes_written; } ;
struct TYPE_7__ {TYPE_1__ egress; } ;
typedef  TYPE_2__ quicly_streambuf_t ;
struct TYPE_8__ {int /*<<< orphan*/  sendstate; TYPE_2__* data; } ;
typedef  TYPE_3__ quicly_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  quicly_sendstate_shutdown (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int quicly_stream_sync_sendbuf (TYPE_3__*,int) ; 

int quicly_streambuf_egress_shutdown(quicly_stream_t *stream)
{
    quicly_streambuf_t *sbuf = stream->data;
    quicly_sendstate_shutdown(&stream->sendstate, sbuf->egress.bytes_written);
    return quicly_stream_sync_sendbuf(stream, 1);
}