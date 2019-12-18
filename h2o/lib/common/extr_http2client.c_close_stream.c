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
struct TYPE_5__ {int /*<<< orphan*/ * body; } ;
struct TYPE_4__ {int /*<<< orphan*/ * buf; int /*<<< orphan*/  sending_link; } ;
struct TYPE_6__ {int /*<<< orphan*/  _timeout; } ;
struct st_h2o_http2client_stream_t {TYPE_2__ input; TYPE_1__ output; TYPE_3__ super; int /*<<< orphan*/ * conn; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct st_h2o_http2client_stream_t*) ; 
 int /*<<< orphan*/  h2o_buffer_dispose (int /*<<< orphan*/ **) ; 
 scalar_t__ h2o_linklist_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_linklist_unlink (int /*<<< orphan*/ *) ; 
 scalar_t__ h2o_timer_is_linked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_stream (struct st_h2o_http2client_stream_t*) ; 

__attribute__((used)) static void close_stream(struct st_h2o_http2client_stream_t *stream)
{
    if (stream->conn != NULL) {
        unregister_stream(stream);
    }

    if (h2o_timer_is_linked(&stream->super._timeout))
        h2o_timer_unlink(&stream->super._timeout);
    if (h2o_linklist_is_linked(&stream->output.sending_link))
        h2o_linklist_unlink(&stream->output.sending_link);

    if (stream->output.buf != NULL)
        h2o_buffer_dispose(&stream->output.buf);
    h2o_buffer_dispose(&stream->input.body);

    free(stream);
}