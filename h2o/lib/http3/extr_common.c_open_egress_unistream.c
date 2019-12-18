#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_http3_egress_unistream_t {TYPE_1__* quic; int /*<<< orphan*/  sendbuf; } ;
struct TYPE_8__ {struct st_h2o_http3_egress_unistream_t* data; } ;
typedef  TYPE_1__ quicly_stream_t ;
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ h2o_iovec_t ;
struct TYPE_10__ {int /*<<< orphan*/  quic; } ;
typedef  TYPE_3__ h2o_http3_conn_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  h2o_buffer_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int quicly_open_stream (int /*<<< orphan*/ ,TYPE_1__**,int) ; 
 int quicly_stream_sync_sendbuf (TYPE_1__*,int) ; 

__attribute__((used)) static int open_egress_unistream(h2o_http3_conn_t *conn, struct st_h2o_http3_egress_unistream_t **stream, h2o_iovec_t initial_bytes)
{
    quicly_stream_t *qs;
    int ret;

    if ((ret = quicly_open_stream(conn->quic, &qs, 1)) != 0)
        return ret;
    *stream = qs->data;
    assert((*stream)->quic == qs);

    h2o_buffer_append(&(*stream)->sendbuf, initial_bytes.base, initial_bytes.len);
    return quicly_stream_sync_sendbuf((*stream)->quic, 1);
}