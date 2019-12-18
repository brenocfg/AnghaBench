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
struct TYPE_5__ {int /*<<< orphan*/  egress; } ;
typedef  TYPE_1__ quicly_streambuf_t ;
struct TYPE_6__ {TYPE_1__* data; } ;
typedef  TYPE_2__ quicly_stream_t ;

/* Variables and functions */
 int quicly_sendbuf_emit (TYPE_2__*,int /*<<< orphan*/ *,size_t,void*,size_t*,int*) ; 

int quicly_streambuf_egress_emit(quicly_stream_t *stream, size_t off, void *dst, size_t *len, int *wrote_all)
{
    quicly_streambuf_t *sbuf = stream->data;
    return quicly_sendbuf_emit(stream, &sbuf->egress, off, dst, len, wrote_all);
}