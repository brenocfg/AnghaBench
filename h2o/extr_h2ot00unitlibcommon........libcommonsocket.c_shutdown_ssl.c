#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/ * write; } ;
struct TYPE_17__ {TYPE_3__* ssl; TYPE_4__ _cb; } ;
typedef  TYPE_5__ h2o_socket_t ;
struct TYPE_13__ {scalar_t__ size; } ;
struct TYPE_14__ {TYPE_1__ bufs; } ;
struct TYPE_15__ {int /*<<< orphan*/ * ossl; TYPE_2__ output; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 scalar_t__ SSL_ERROR_WANT_READ ; 
 scalar_t__ SSL_get_error (int /*<<< orphan*/ *,int) ; 
 int SSL_shutdown (int /*<<< orphan*/ *) ; 
 void dispose_socket (TYPE_5__*,char const*) ; 
 int /*<<< orphan*/  flush_pending_ssl (TYPE_5__*,void (*) (TYPE_5__*,char const*)) ; 
 int /*<<< orphan*/  h2o_socket_read_start (TYPE_5__*,void (*) (TYPE_5__*,char const*)) ; 
 int /*<<< orphan*/  h2o_socket_read_stop (TYPE_5__*) ; 

__attribute__((used)) static void shutdown_ssl(h2o_socket_t *sock, const char *err)
{
    int ret;

    if (err != NULL)
        goto Close;

    if (sock->_cb.write != NULL) {
        /* note: libuv calls the write callback after the socket is closed by uv_close (with status set to 0 if the write succeeded)
         */
        sock->_cb.write = NULL;
        goto Close;
    }

#if H2O_USE_PICOTLS
    if (sock->ssl->ptls != NULL) {
        ptls_buffer_t wbuf;
        uint8_t wbuf_small[32];
        ptls_buffer_init(&wbuf, wbuf_small, sizeof(wbuf_small));
        if ((ret = ptls_send_alert(sock->ssl->ptls, &wbuf, PTLS_ALERT_LEVEL_WARNING, PTLS_ALERT_CLOSE_NOTIFY)) != 0)
            goto Close;
        write_ssl_bytes(sock, wbuf.base, wbuf.off);
        ptls_buffer_dispose(&wbuf);
        ret = 1; /* close the socket after sending close_notify */
    } else
#endif
        if (sock->ssl->ossl != NULL) {
        ERR_clear_error();
        if ((ret = SSL_shutdown(sock->ssl->ossl)) == -1)
            goto Close;
    } else {
        goto Close;
    }

    if (sock->ssl->output.bufs.size != 0) {
        h2o_socket_read_stop(sock);
        flush_pending_ssl(sock, ret == 1 ? dispose_socket : shutdown_ssl);
    } else if (ret == 2 && SSL_get_error(sock->ssl->ossl, ret) == SSL_ERROR_WANT_READ) {
        h2o_socket_read_start(sock, shutdown_ssl);
    } else {
        goto Close;
    }

    return;
Close:
    dispose_socket(sock, err);
}