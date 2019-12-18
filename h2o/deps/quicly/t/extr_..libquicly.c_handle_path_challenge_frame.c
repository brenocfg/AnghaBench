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
struct st_quicly_handle_payload_state_t {int /*<<< orphan*/  end; int /*<<< orphan*/  src; } ;
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ quicly_path_challenge_frame_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;

/* Variables and functions */
 int quicly_decode_path_challenge_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int schedule_path_challenge (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_path_challenge_frame(quicly_conn_t *conn, struct st_quicly_handle_payload_state_t *state)
{
    quicly_path_challenge_frame_t frame;
    int ret;

    if ((ret = quicly_decode_path_challenge_frame(&state->src, state->end, &frame)) != 0)
        return ret;
    return schedule_path_challenge(conn, 1, frame.data);
}