#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ res; scalar_t__ req; } ;
struct st_h2o_http2client_stream_t {TYPE_1__ state; } ;

/* Variables and functions */
 scalar_t__ STREAM_STATE_CLOSED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  close_stream (struct st_h2o_http2client_stream_t*) ; 

__attribute__((used)) static void close_response(struct st_h2o_http2client_stream_t *stream)
{
    assert(stream->state.res != STREAM_STATE_CLOSED);
    stream->state.res = STREAM_STATE_CLOSED;
    if (stream->state.req == STREAM_STATE_CLOSED) {
        close_stream(stream);
    }
}