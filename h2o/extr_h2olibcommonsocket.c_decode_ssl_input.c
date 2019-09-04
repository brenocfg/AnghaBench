#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_8__* input; TYPE_4__* ssl; } ;
typedef  TYPE_5__ h2o_socket_t ;
struct TYPE_15__ {scalar_t__ len; int /*<<< orphan*/ * base; } ;
typedef  TYPE_6__ h2o_iovec_t ;
struct TYPE_16__ {int size; } ;
struct TYPE_12__ {TYPE_2__* encrypted; } ;
struct TYPE_10__ {int /*<<< orphan*/ * cb; } ;
struct TYPE_13__ {int* did_write_in_read; int /*<<< orphan*/  ossl; TYPE_3__ input; TYPE_1__ handshake; } ;
struct TYPE_11__ {scalar_t__ size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 scalar_t__ SSL_ERROR_WANT_READ ; 
 scalar_t__ SSL_get_error (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SSL_pending (int /*<<< orphan*/ ) ; 
 int SSL_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_6__ h2o_buffer_reserve (TYPE_8__**,int) ; 
 char const* h2o_socket_error_out_of_memory ; 
 char const* h2o_socket_error_ssl_decode ; 

const char *decode_ssl_input(h2o_socket_t *sock)
{
    assert(sock->ssl != NULL);
    assert(sock->ssl->handshake.cb == NULL);

#if H2O_USE_PICOTLS
    if (sock->ssl->ptls != NULL) {
        if (sock->ssl->input.encrypted->size != 0) {
            const char *src = sock->ssl->input.encrypted->bytes, *src_end = src + sock->ssl->input.encrypted->size;
            h2o_iovec_t reserved;
            ptls_buffer_t rbuf;
            int ret;
            if ((reserved = h2o_buffer_reserve(&sock->input, sock->ssl->input.encrypted->size)).base == NULL)
                return h2o_socket_error_out_of_memory;
            ptls_buffer_init(&rbuf, reserved.base, reserved.len);
            do {
                size_t consumed = src_end - src;
                if ((ret = ptls_receive(sock->ssl->ptls, &rbuf, src, &consumed)) != 0)
                    break;
                src += consumed;
            } while (src != src_end);
            h2o_buffer_consume(&sock->ssl->input.encrypted, sock->ssl->input.encrypted->size - (src_end - src));
            if (rbuf.is_allocated) {
                if ((reserved = h2o_buffer_reserve(&sock->input, rbuf.off)).base == NULL)
                    return h2o_socket_error_out_of_memory;
                memcpy(reserved.base, rbuf.base, rbuf.off);
                sock->input->size += rbuf.off;
                ptls_buffer_dispose(&rbuf);
            } else {
                sock->input->size += rbuf.off;
            }
            if (!(ret == 0 || ret == PTLS_ERROR_IN_PROGRESS))
                return h2o_socket_error_ssl_decode;
        }
        return NULL;
    }
#endif

    while (sock->ssl->input.encrypted->size != 0 || SSL_pending(sock->ssl->ossl)) {
        int rlen;
        h2o_iovec_t buf = h2o_buffer_reserve(&sock->input, 4096);
        if (buf.base == NULL)
            return h2o_socket_error_out_of_memory;
        { /* call SSL_read (while detecting SSL renegotiation and reporting it as error) */
            int did_write_in_read = 0;
            sock->ssl->did_write_in_read = &did_write_in_read;
            ERR_clear_error();
            rlen = SSL_read(sock->ssl->ossl, buf.base, (int)buf.len);
            sock->ssl->did_write_in_read = NULL;
            if (did_write_in_read)
                return "ssl renegotiation not supported";
        }
        if (rlen == -1) {
            if (SSL_get_error(sock->ssl->ossl, rlen) != SSL_ERROR_WANT_READ) {
                return h2o_socket_error_ssl_decode;
            }
            break;
        } else if (rlen == 0) {
            break;
        } else {
            sock->input->size += rlen;
        }
    }

    return 0;
}