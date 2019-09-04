#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
struct st_h2o_evloop_socket_t {int /*<<< orphan*/  _flags; } ;
struct TYPE_16__ {int state; size_t suggested_tls_payload_size; } ;
struct TYPE_17__ {size_t bytes_written; TYPE_11__* ssl; TYPE_3__ _latency_optimization; } ;
typedef  TYPE_4__ h2o_socket_t ;
typedef  int /*<<< orphan*/  h2o_socket_cb ;
struct TYPE_18__ {size_t len; scalar_t__ base; } ;
typedef  TYPE_5__ h2o_iovec_t ;
struct TYPE_14__ {scalar_t__ size; } ;
struct TYPE_15__ {TYPE_1__ bufs; } ;
struct TYPE_13__ {int /*<<< orphan*/  ossl; TYPE_2__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_SOCKET_FLAG_IS_WRITE_ERROR ; 
#define  H2O_SOCKET_LATENCY_OPTIMIZATION_STATE_DETERMINED 130 
#define  H2O_SOCKET_LATENCY_OPTIMIZATION_STATE_DISABLED 129 
 int H2O_SOCKET_LATENCY_OPTIMIZATION_STATE_NEEDS_UPDATE ; 
#define  H2O_SOCKET_LATENCY_OPTIMIZATION_STATE_TBD 128 
 int SSL_write (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int calc_suggested_tls_payload_size (TYPE_4__*,int) ; 
 int /*<<< orphan*/  clear_output_buffer (TYPE_11__*) ; 
 int /*<<< orphan*/  do_write (TYPE_4__*,TYPE_5__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_pending_ssl (TYPE_4__*,int /*<<< orphan*/ ) ; 

void h2o_socket_write(h2o_socket_t *sock, h2o_iovec_t *bufs, size_t bufcnt, h2o_socket_cb cb)
{
    size_t i, prev_bytes_written = sock->bytes_written;

    assert(bufcnt > 0);
    for (i = 0; i != bufcnt; ++i) {
        sock->bytes_written += bufs[i].len;
#if H2O_SOCKET_DUMP_WRITE
        h2o_error_printf("writing %zu bytes to fd:%d\n", bufs[i].len, h2o_socket_get_fd(sock));
        h2o_dump_memory(stderr, bufs[i].base, bufs[i].len);
#endif
    }

    if (sock->ssl == NULL) {
        do_write(sock, bufs, bufcnt, cb);
    } else {
        assert(sock->ssl->output.bufs.size == 0);
        /* fill in the data */
        size_t ssl_record_size;
        switch (sock->_latency_optimization.state) {
        case H2O_SOCKET_LATENCY_OPTIMIZATION_STATE_TBD:
        case H2O_SOCKET_LATENCY_OPTIMIZATION_STATE_DISABLED:
            ssl_record_size = prev_bytes_written < 200 * 1024 ? calc_suggested_tls_payload_size(sock, 1400) : 16384;
            break;
        case H2O_SOCKET_LATENCY_OPTIMIZATION_STATE_DETERMINED:
            sock->_latency_optimization.state = H2O_SOCKET_LATENCY_OPTIMIZATION_STATE_NEEDS_UPDATE;
        /* fallthru */
        default:
            ssl_record_size = sock->_latency_optimization.suggested_tls_payload_size;
            break;
        }
        for (; bufcnt != 0; ++bufs, --bufcnt) {
            size_t off = 0;
            while (off != bufs[0].len) {
                int ret;
                size_t sz = bufs[0].len - off;
                if (sz > ssl_record_size)
                    sz = ssl_record_size;
#if H2O_USE_PICOTLS
                if (sock->ssl->ptls != NULL) {
                    size_t dst_size = sz + ptls_get_record_overhead(sock->ssl->ptls);
                    void *dst = h2o_mem_alloc_pool(&sock->ssl->output.pool, char, dst_size);
                    ptls_buffer_t wbuf;
                    ptls_buffer_init(&wbuf, dst, dst_size);
                    ret = ptls_send(sock->ssl->ptls, &wbuf, bufs[0].base + off, sz);
                    assert(ret == 0);
                    dst_size = wbuf.off;
                    if (wbuf.is_allocated) {
                        /* happens when ptls_send emits KeyUpdate message, for one case due to receiving one from peer */
                        dst = h2o_mem_alloc_pool(&sock->ssl->output.pool, char, dst_size);
                        memcpy(dst, wbuf.base, dst_size);
                        ptls_buffer_dispose(&wbuf);
                    }
                    h2o_vector_reserve(&sock->ssl->output.pool, &sock->ssl->output.bufs, sock->ssl->output.bufs.size + 1);
                    sock->ssl->output.bufs.entries[sock->ssl->output.bufs.size++] = h2o_iovec_init(dst, dst_size);
                } else
#endif
                {
                    ret = SSL_write(sock->ssl->ossl, bufs[0].base + off, (int)sz);
                    if (ret != sz) {
                        /* The error happens if SSL_write is called after SSL_read returns a fatal error (e.g. due to corrupt TCP
                         * packet being received). We need to take care of this since some protocol implementations send data after
                         * the read-side of the connection gets closed (note that protocol implementations are (yet) incapable of
                         * distinguishing a normal shutdown and close due to an error using the `status` value of the read
                         * callback).
                         */
                        clear_output_buffer(sock->ssl);
                        flush_pending_ssl(sock, cb);
#ifndef H2O_USE_LIBUV
                        ((struct st_h2o_evloop_socket_t *)sock)->_flags |= H2O_SOCKET_FLAG_IS_WRITE_ERROR;
#endif
                        return;
                    }
                }
                off += sz;
            }
        }
        flush_pending_ssl(sock, cb);
    }
}