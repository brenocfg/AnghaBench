#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;

/* Type definitions */
struct TYPE_19__ {int off; int /*<<< orphan*/  base; scalar_t__ is_allocated; } ;
typedef  TYPE_4__ ptls_buffer_t ;
struct TYPE_20__ {TYPE_11__* input; TYPE_3__* ssl; } ;
typedef  TYPE_5__ h2o_socket_t ;
struct TYPE_21__ {scalar_t__ len; int /*<<< orphan*/ * base; } ;
typedef  TYPE_6__ h2o_iovec_t ;
struct TYPE_17__ {TYPE_12__* encrypted; } ;
struct TYPE_16__ {int /*<<< orphan*/ * cb; } ;
struct TYPE_18__ {int* did_write_in_read; int /*<<< orphan*/  ossl; TYPE_2__ input; int /*<<< orphan*/ * ptls; TYPE_1__ handshake; } ;
struct TYPE_15__ {scalar_t__ size; char* bytes; } ;
struct TYPE_14__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 int PTLS_ERROR_IN_PROGRESS ; 
 scalar_t__ SSL_ERROR_WANT_READ ; 
 scalar_t__ SSL_get_error (int /*<<< orphan*/ ,int) ; 
 scalar_t__ SSL_pending (int /*<<< orphan*/ ) ; 
 int SSL_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_12__**,int) ; 
 TYPE_6__ h2o_buffer_try_reserve (TYPE_11__**,int) ; 
 char const* h2o_socket_error_out_of_memory ; 
 char const* h2o_socket_error_ssl_decode ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ptls_buffer_dispose (TYPE_4__*) ; 
 int /*<<< orphan*/  ptls_buffer_init (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int ptls_receive (int /*<<< orphan*/ *,TYPE_4__*,char const*,size_t*) ; 

const char *decode_ssl_input(h2o_socket_t *sock)
{
    assert(sock->ssl != NULL);
    assert(sock->ssl->handshake.cb == NULL);

    if (sock->ssl->ptls != NULL) {
        if (sock->ssl->input.encrypted->size != 0) {
            const char *src = sock->ssl->input.encrypted->bytes, *src_end = src + sock->ssl->input.encrypted->size;
            h2o_iovec_t reserved;
            ptls_buffer_t rbuf;
            int ret;
            if ((reserved = h2o_buffer_try_reserve(&sock->input, sock->ssl->input.encrypted->size)).base == NULL)
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
                if ((reserved = h2o_buffer_try_reserve(&sock->input, rbuf.off)).base == NULL)
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

    while (sock->ssl->input.encrypted->size != 0 || SSL_pending(sock->ssl->ossl)) {
        int rlen;
        h2o_iovec_t buf = h2o_buffer_try_reserve(&sock->input, 4096);
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