#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_23__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_18__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
struct TYPE_26__ {int /*<<< orphan*/ * write; } ;
struct TYPE_35__ {TYPE_23__* ssl; TYPE_1__ _cb; } ;
typedef  TYPE_9__ h2o_socket_t ;
struct TYPE_24__ {int len; int /*<<< orphan*/  base; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_10__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  X509 ;
struct TYPE_34__ {TYPE_18__* encrypted; } ;
struct TYPE_32__ {int /*<<< orphan*/  server_name; } ;
struct TYPE_28__ {int state; } ;
struct TYPE_29__ {TYPE_2__ async_resumption; } ;
struct TYPE_33__ {TYPE_6__ client; TYPE_3__ server; } ;
struct TYPE_30__ {scalar_t__ size; } ;
struct TYPE_31__ {TYPE_4__ bufs; } ;
struct TYPE_27__ {TYPE_8__ input; TYPE_7__ handshake; int /*<<< orphan*/ * ossl; TYPE_5__ output; } ;
struct TYPE_25__ {int size; int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
#define  ASYNC_RESUMPTION_STATE_COMPLETE 132 
#define  ASYNC_RESUMPTION_STATE_RECORD 131 
#define  ASYNC_RESUMPTION_STATE_REQUEST_SENT 130 
 int /*<<< orphan*/  ERR_clear_error () ; 
#define  MatchFound 129 
#define  MatchNotFound 128 
 scalar_t__ SSL_ERROR_WANT_READ ; 
 int SSL_accept (int /*<<< orphan*/ *) ; 
 int SSL_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_get_error (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * SSL_get_peer_certificate (int /*<<< orphan*/ *) ; 
 long SSL_get_verify_result (int /*<<< orphan*/ *) ; 
 scalar_t__ SSL_is_server (int /*<<< orphan*/ *) ; 
 long X509_V_OK ; 
 int /*<<< orphan*/  X509_free (int /*<<< orphan*/ *) ; 
 char* X509_verify_cert_error_string (long) ; 
 int /*<<< orphan*/  alloca (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_output_buffer (TYPE_23__*) ; 
 int /*<<< orphan*/  create_ossl (TYPE_9__*) ; 
 int /*<<< orphan*/  flush_pending_ssl (TYPE_9__*,void (*) (TYPE_9__*,char const*)) ; 
 int /*<<< orphan*/  h2o_buffer_consume (TYPE_18__**,int) ; 
 int /*<<< orphan*/  h2o_buffer_reserve (TYPE_18__**,int) ; 
 int /*<<< orphan*/  h2o_fatal (char*) ; 
 TYPE_10__ h2o_iovec_init (int /*<<< orphan*/ ,int) ; 
 char* h2o_socket_error_ssl_cert_invalid ; 
 char* h2o_socket_error_ssl_cert_name_mismatch ; 
 char* h2o_socket_error_ssl_handshake ; 
 char* h2o_socket_error_ssl_no_cert ; 
 int /*<<< orphan*/  h2o_socket_read_start (TYPE_9__*,void (*) (TYPE_9__*,char const*)) ; 
 int /*<<< orphan*/  h2o_socket_read_stop (TYPE_9__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void on_handshake_complete (TYPE_9__*,char const*) ; 
 void on_handshake_failure_ossl111 (TYPE_9__*,char const*) ; 
 int validate_hostname (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void proceed_handshake(h2o_socket_t *sock, const char *err)
{
    h2o_iovec_t first_input = {NULL};
    int ret = 0;

    sock->_cb.write = NULL;

    if (err != NULL) {
        goto Complete;
    }

    if (sock->ssl->ossl == NULL) {
#if H2O_USE_PICOTLS
        /* prepare I/O */
        size_t consumed = sock->ssl->input.encrypted->size;
        ptls_buffer_t wbuf;
        ptls_buffer_init(&wbuf, "", 0);

        if (sock->ssl->ptls != NULL) {
            /* picotls in action, proceed the handshake */
            ret = ptls_handshake(sock->ssl->ptls, &wbuf, sock->ssl->input.encrypted->bytes, &consumed, NULL);
        } else {
            /* start using picotls if the first packet contains TLS 1.3 CH */
            ptls_context_t *ptls_ctx = h2o_socket_ssl_get_picotls_context(sock->ssl->ssl_ctx);
            if (ptls_ctx != NULL) {
                ptls_t *ptls = ptls_new(ptls_ctx, 1);
                if (ptls == NULL)
                    h2o_fatal("no memory");
                ret = ptls_handshake(ptls, &wbuf, sock->ssl->input.encrypted->bytes, &consumed, NULL);
                if ((ret == 0 || ret == PTLS_ERROR_IN_PROGRESS) && wbuf.off != 0) {
                    sock->ssl->ptls = ptls;
                    sock->ssl->handshake.server.async_resumption.state = ASYNC_RESUMPTION_STATE_COMPLETE;
                } else {
                    ptls_free(ptls);
                }
            }
        }

        if (sock->ssl->ptls != NULL) {
            /* complete I/O done by picotls */
            h2o_buffer_consume(&sock->ssl->input.encrypted, consumed);
            switch (ret) {
            case 0:
            case PTLS_ERROR_IN_PROGRESS:
                if (wbuf.off != 0) {
                    h2o_socket_read_stop(sock);
                    write_ssl_bytes(sock, wbuf.base, wbuf.off);
                    flush_pending_ssl(sock, ret == 0 ? on_handshake_complete : proceed_handshake);
                } else {
                    h2o_socket_read_start(sock, proceed_handshake);
                }
                break;
            default:
                /* FIXME send alert in wbuf before calling the callback */
                on_handshake_complete(sock, "picotls handshake error");
                break;
            }
            ptls_buffer_dispose(&wbuf);
            return;
        }
        ptls_buffer_dispose(&wbuf);
#endif

        /* fallback to openssl if the attempt failed */
        create_ossl(sock);
    }

    if (sock->ssl->ossl != NULL && SSL_is_server(sock->ssl->ossl) &&
        sock->ssl->handshake.server.async_resumption.state == ASYNC_RESUMPTION_STATE_RECORD) {
        if (sock->ssl->input.encrypted->size <= 1024) {
            /* retain a copy of input if performing async resumption */
            first_input = h2o_iovec_init(alloca(sock->ssl->input.encrypted->size), sock->ssl->input.encrypted->size);
            memcpy(first_input.base, sock->ssl->input.encrypted->bytes, first_input.len);
        } else {
            sock->ssl->handshake.server.async_resumption.state = ASYNC_RESUMPTION_STATE_COMPLETE;
        }
    }

Redo:
    ERR_clear_error();
    if (SSL_is_server(sock->ssl->ossl)) {
        ret = SSL_accept(sock->ssl->ossl);
        switch (sock->ssl->handshake.server.async_resumption.state) {
        case ASYNC_RESUMPTION_STATE_COMPLETE:
            break;
        case ASYNC_RESUMPTION_STATE_RECORD:
            /* async resumption has not been triggered; proceed the state to complete */
            sock->ssl->handshake.server.async_resumption.state = ASYNC_RESUMPTION_STATE_COMPLETE;
            break;
        case ASYNC_RESUMPTION_STATE_REQUEST_SENT: {
            /* sent async request, reset the ssl state, and wait for async response */
            assert(ret < 0);
            SSL_free(sock->ssl->ossl);
            create_ossl(sock);
            clear_output_buffer(sock->ssl);
            h2o_buffer_consume(&sock->ssl->input.encrypted, sock->ssl->input.encrypted->size);
            h2o_buffer_reserve(&sock->ssl->input.encrypted, first_input.len);
            memcpy(sock->ssl->input.encrypted->bytes, first_input.base, first_input.len);
            sock->ssl->input.encrypted->size = first_input.len;
            h2o_socket_read_stop(sock);
            return;
        }
        default:
            h2o_fatal("unexpected async resumption state");
            break;
        }
    } else {
        ret = SSL_connect(sock->ssl->ossl);
    }

    if (ret == 0 || (ret < 0 && SSL_get_error(sock->ssl->ossl, ret) != SSL_ERROR_WANT_READ)) {
        /* failed */
        long verify_result = SSL_get_verify_result(sock->ssl->ossl);
        if (verify_result != X509_V_OK) {
            err = X509_verify_cert_error_string(verify_result);
        } else {
            err = h2o_socket_error_ssl_handshake;
            /* OpenSSL 1.1.0 emits an alert immediately, we  send it now. 1.0.2 emits the error when SSL_shutdown is called in
             * shutdown_ssl. */
            if (sock->ssl->output.bufs.size != 0) {
                h2o_socket_read_stop(sock);
                flush_pending_ssl(sock, on_handshake_failure_ossl111);
                return;
            }
        }
        goto Complete;
    }

    if (sock->ssl->output.bufs.size != 0) {
        h2o_socket_read_stop(sock);
        flush_pending_ssl(sock, ret == 1 ? on_handshake_complete : proceed_handshake);
    } else {
        if (ret == 1) {
            if (!SSL_is_server(sock->ssl->ossl)) {
                X509 *cert = SSL_get_peer_certificate(sock->ssl->ossl);
                if (cert != NULL) {
                    switch (validate_hostname(sock->ssl->handshake.client.server_name, cert)) {
                    case MatchFound:
                        /* ok */
                        break;
                    case MatchNotFound:
                        err = h2o_socket_error_ssl_cert_name_mismatch;
                        break;
                    default:
                        err = h2o_socket_error_ssl_cert_invalid;
                        break;
                    }
                    X509_free(cert);
                } else {
                    err = h2o_socket_error_ssl_no_cert;
                }
            }
            goto Complete;
        }
        if (sock->ssl->input.encrypted->size != 0)
            goto Redo;
        h2o_socket_read_start(sock, proceed_handshake);
    }
    return;

Complete:
    h2o_socket_read_stop(sock);
    on_handshake_complete(sock, err);
}