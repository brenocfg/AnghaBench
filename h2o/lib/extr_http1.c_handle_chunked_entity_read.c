#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* ctx; } ;
struct TYPE_7__ {scalar_t__ req_body_bytes_received; } ;
struct st_h2o_http1_conn_t {TYPE_5__* sock; TYPE_4__ super; TYPE_1__ req; scalar_t__ _req_entity_reader; } ;
struct st_h2o_http1_chunked_entity_reader {int /*<<< orphan*/  decoder; } ;
typedef  int ssize_t ;
struct TYPE_12__ {size_t size; int /*<<< orphan*/  bytes; } ;
struct TYPE_11__ {TYPE_6__* input; } ;
struct TYPE_9__ {TYPE_2__* globalconf; } ;
struct TYPE_8__ {scalar_t__ max_request_entity_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  entity_read_send_error_400 (struct st_h2o_http1_conn_t*,char*,char*) ; 
 int /*<<< orphan*/  entity_read_send_error_413 (struct st_h2o_http1_conn_t*,char*,char*) ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_6__**,size_t) ; 
 int /*<<< orphan*/  handle_one_body_fragment (struct st_h2o_http1_conn_t*,size_t,int) ; 
 int phr_decode_chunked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static void handle_chunked_entity_read(struct st_h2o_http1_conn_t *conn)
{
    struct st_h2o_http1_chunked_entity_reader *reader = (void *)conn->_req_entity_reader;
    size_t bufsz, consume;
    ssize_t ret;
    int complete = 1;

    /* decode the incoming data */
    if ((consume = bufsz = conn->sock->input->size) == 0)
        return;
    ret = phr_decode_chunked(&reader->decoder, conn->sock->input->bytes, &bufsz);
    if (ret != -1 && bufsz + conn->req.req_body_bytes_received >= conn->super.ctx->globalconf->max_request_entity_size) {
        entity_read_send_error_413(conn, "Request Entity Too Large", "request entity is too large");
        return;
    }
    if (ret < 0) {
        if (ret == -2) {
            /* incomplete */
            complete = 0;
            goto Done;
        }
        /* error */
        entity_read_send_error_400(conn, "Invalid Request", "broken chunked-encoding");
        return;
    }
    /* complete */
    consume -= ret;
Done:
    handle_one_body_fragment(conn, bufsz, complete);
    h2o_buffer_consume(&conn->sock->input, consume - bufsz);
}