#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int stop_sending; } ;
struct TYPE_6__ {TYPE_1__ error_received; } ;
typedef  TYPE_2__ test_streambuf_t ;
struct TYPE_7__ {TYPE_2__* data; } ;
typedef  TYPE_3__ quicly_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  QUICLY_ERROR_IS_QUIC_APPLICATION (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int on_egress_stop(quicly_stream_t *stream, int err)
{
    assert(QUICLY_ERROR_IS_QUIC_APPLICATION(err));
    test_streambuf_t *sbuf = stream->data;
    sbuf->error_received.stop_sending = err;
    return 0;
}