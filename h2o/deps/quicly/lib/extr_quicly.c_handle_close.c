#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_12__ {scalar_t__ state; TYPE_1__* ctx; } ;
struct TYPE_13__ {TYPE_2__ super; } ;
typedef  TYPE_3__ quicly_conn_t ;
struct TYPE_14__ {int /*<<< orphan*/  len; scalar_t__ base; } ;
typedef  TYPE_4__ ptls_iovec_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* cb ) (TYPE_5__*,TYPE_3__*,int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {TYPE_5__* closed_by_peer; } ;

/* Variables and functions */
 int QUICLY_ERROR_RECEIVED_STATELESS_RESET ; 
 scalar_t__ QUICLY_STATE_CLOSING ; 
 int /*<<< orphan*/  destroy_all_streams (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int enter_close (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,TYPE_3__*,int,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_close(quicly_conn_t *conn, int err, uint64_t frame_type, ptls_iovec_t reason_phrase)
{
    int ret;

    if (conn->super.state >= QUICLY_STATE_CLOSING)
        return 0;

    /* switch to closing state, notify the app (at this moment the streams are accessible), then destroy the streams */
    if ((ret = enter_close(conn, 0, err != QUICLY_ERROR_RECEIVED_STATELESS_RESET)) != 0)
        return ret;
    if (conn->super.ctx->closed_by_peer != NULL)
        conn->super.ctx->closed_by_peer->cb(conn->super.ctx->closed_by_peer, conn, err, frame_type,
                                            (const char *)reason_phrase.base, reason_phrase.len);
    destroy_all_streams(conn, err, 0);

    return 0;
}