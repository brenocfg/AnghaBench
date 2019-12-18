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
struct TYPE_6__ {int stop_sending; int reset_stream; } ;
struct TYPE_7__ {TYPE_1__ error_received; } ;
typedef  TYPE_2__ test_streambuf_t ;
struct TYPE_8__ {int /*<<< orphan*/ * callbacks; TYPE_2__* data; } ;
typedef  TYPE_3__ quicly_stream_t ;
typedef  int /*<<< orphan*/  quicly_stream_open_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int quicly_streambuf_create (TYPE_3__*,int) ; 
 int /*<<< orphan*/  stream_callbacks ; 

__attribute__((used)) static int on_stream_open(quicly_stream_open_t *self, quicly_stream_t *stream)
{
    test_streambuf_t *sbuf;
    int ret;

    ret = quicly_streambuf_create(stream, sizeof(*sbuf));
    assert(ret == 0);
    sbuf = stream->data;
    sbuf->error_received.stop_sending = -1;
    sbuf->error_received.reset_stream = -1;
    stream->callbacks = &stream_callbacks;

    return 0;
}