#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  khiter_t ;
struct TYPE_7__ {int /*<<< orphan*/ * enc; int /*<<< orphan*/ * dec; } ;
struct TYPE_8__ {int /*<<< orphan*/  _timeout; int /*<<< orphan*/ * quic; TYPE_5__* ctx; TYPE_1__ qpack; } ;
typedef  TYPE_2__ h2o_http3_conn_t ;
struct TYPE_10__ {int /*<<< orphan*/  conns_by_id; } ;
struct TYPE_9__ {int /*<<< orphan*/  master_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  drop_from_acceptmap (TYPE_5__*,TYPE_2__*) ; 
 int /*<<< orphan*/  h2o_qpack_destroy_decoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_qpack_destroy_encoder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kh_del_h2o_http3_idmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kh_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kh_get_h2o_http3_idmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quicly_free (int /*<<< orphan*/ *) ; 
 TYPE_3__* quicly_get_master_id (int /*<<< orphan*/ *) ; 

void h2o_http3_dispose_conn(h2o_http3_conn_t *conn)
{
    if (conn->qpack.dec != NULL)
        h2o_qpack_destroy_decoder(conn->qpack.dec);
    if (conn->qpack.enc != NULL)
        h2o_qpack_destroy_encoder(conn->qpack.enc);
    if (conn->quic != NULL) {
        khiter_t iter;
        /* unregister from maps */
        if ((iter = kh_get_h2o_http3_idmap(conn->ctx->conns_by_id, quicly_get_master_id(conn->quic)->master_id)) !=
            kh_end(conn->ctx->conns_by_id))
            kh_del_h2o_http3_idmap(conn->ctx->conns_by_id, iter);
        drop_from_acceptmap(conn->ctx, conn);
        quicly_free(conn->quic);
    }
    h2o_timer_unlink(&conn->_timeout);
}