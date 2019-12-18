#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct st_quicly_handle_payload_state_t {scalar_t__ epoch; int /*<<< orphan*/  end; int /*<<< orphan*/  src; } ;
typedef  int /*<<< orphan*/  quicly_stream_t ;
typedef  int /*<<< orphan*/  quicly_stream_id_t ;
typedef  int /*<<< orphan*/  quicly_stream_frame_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;

/* Variables and functions */
 int apply_stream_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int quicly_decode_crypto_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * quicly_get_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_crypto_frame(quicly_conn_t *conn, struct st_quicly_handle_payload_state_t *state)
{
    quicly_stream_frame_t frame;
    quicly_stream_t *stream;
    int ret;

    if ((ret = quicly_decode_crypto_frame(&state->src, state->end, &frame)) != 0)
        return ret;
    stream = quicly_get_stream(conn, -(quicly_stream_id_t)(1 + state->epoch));
    assert(stream != NULL);
    return apply_stream_frame(stream, &frame);
}