#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct st_quicly_handle_payload_state_t {int /*<<< orphan*/  end; int /*<<< orphan*/  src; } ;
struct TYPE_16__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_13__ {TYPE_7__ token; } ;
typedef  TYPE_3__ quicly_new_token_frame_t ;
struct TYPE_12__ {TYPE_1__* ctx; } ;
struct TYPE_14__ {TYPE_2__ super; } ;
typedef  TYPE_4__ quicly_conn_t ;
struct TYPE_15__ {int (* cb ) (TYPE_5__*,TYPE_4__*,TYPE_7__) ;} ;
struct TYPE_11__ {TYPE_5__* save_resumption_token; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEW_TOKEN_RECEIVE ; 
 int /*<<< orphan*/  QUICLY_PROBE (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe_now () ; 
 int quicly_decode_new_token_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int stub1 (TYPE_5__*,TYPE_4__*,TYPE_7__) ; 

__attribute__((used)) static int handle_new_token_frame(quicly_conn_t *conn, struct st_quicly_handle_payload_state_t *state)
{
    quicly_new_token_frame_t frame;
    int ret;

    if ((ret = quicly_decode_new_token_frame(&state->src, state->end, &frame)) != 0)
        return ret;
    QUICLY_PROBE(NEW_TOKEN_RECEIVE, conn, probe_now(), frame.token.base, frame.token.len);
    if (conn->super.ctx->save_resumption_token == NULL)
        return 0;
    return conn->super.ctx->save_resumption_token->cb(conn->super.ctx->save_resumption_token, conn, frame.token);
}