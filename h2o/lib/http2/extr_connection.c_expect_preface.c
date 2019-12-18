#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t ssize_t ;
struct TYPE_13__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ h2o_iovec_t ;
struct TYPE_12__ {TYPE_4__* buf; } ;
struct TYPE_14__ {int /*<<< orphan*/  _read_expect; int /*<<< orphan*/ * http2_origin_frame; TYPE_1__ _write; } ;
typedef  TYPE_3__ h2o_http2_conn_t ;
struct TYPE_16__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
struct TYPE_15__ {int /*<<< orphan*/  size; } ;
struct TYPE_11__ {size_t len; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 TYPE_10__ CONNECTION_PREFACE ; 
 size_t H2O_HTTP2_ERROR_INCOMPLETE ; 
 size_t H2O_HTTP2_ERROR_PROTOCOL_CLOSE_IMMEDIATELY ; 
 TYPE_9__ SERVER_PREFACE ; 
 int /*<<< orphan*/  expect_default ; 
 TYPE_2__ h2o_buffer_reserve (TYPE_4__**,scalar_t__) ; 
 int /*<<< orphan*/  h2o_http2_conn_request_write (TYPE_3__*) ; 
 int /*<<< orphan*/  h2o_http2_encode_origin_frame (TYPE_4__**,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ssize_t expect_preface(h2o_http2_conn_t *conn, const uint8_t *src, size_t len, const char **err_desc)
{
    if (len < CONNECTION_PREFACE.len) {
        return H2O_HTTP2_ERROR_INCOMPLETE;
    }
    if (memcmp(src, CONNECTION_PREFACE.base, CONNECTION_PREFACE.len) != 0) {
        return H2O_HTTP2_ERROR_PROTOCOL_CLOSE_IMMEDIATELY;
    }

    { /* send SETTINGS and connection-level WINDOW_UPDATE */
        h2o_iovec_t vec = h2o_buffer_reserve(&conn->_write.buf, SERVER_PREFACE.len);
        memcpy(vec.base, SERVER_PREFACE.base, SERVER_PREFACE.len);
        conn->_write.buf->size += SERVER_PREFACE.len;
        if (conn->http2_origin_frame) {
            /* write origin frame */
            h2o_http2_encode_origin_frame(&conn->_write.buf, *conn->http2_origin_frame);
        }
        h2o_http2_conn_request_write(conn);
    }

    conn->_read_expect = expect_default;
    return CONNECTION_PREFACE.len;
}