#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_4__* ssl; } ;
typedef  TYPE_5__ h2o_socket_t ;
struct TYPE_15__ {scalar_t__ len; scalar_t__ base; } ;
typedef  TYPE_6__ h2o_iovec_t ;
struct TYPE_10__ {int /*<<< orphan*/ * session_data; int /*<<< orphan*/  state; } ;
struct TYPE_11__ {TYPE_1__ async_resumption; } ;
struct TYPE_12__ {TYPE_2__ server; } ;
struct TYPE_13__ {TYPE_3__ handshake; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_RESUMPTION_STATE_COMPLETE ; 
 int /*<<< orphan*/  SSL_SESSION_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * d2i_SSL_SESSION (int /*<<< orphan*/ *,unsigned char const**,long) ; 
 int /*<<< orphan*/  proceed_handshake (TYPE_5__*,int /*<<< orphan*/ ) ; 

void h2o_socket_ssl_resume_server_handshake(h2o_socket_t *sock, h2o_iovec_t session_data)
{
    if (session_data.len != 0) {
        const unsigned char *p = (void *)session_data.base;
        sock->ssl->handshake.server.async_resumption.session_data = d2i_SSL_SESSION(NULL, &p, (long)session_data.len);
        /* FIXME warn on failure */
    }

    sock->ssl->handshake.server.async_resumption.state = ASYNC_RESUMPTION_STATE_COMPLETE;
    proceed_handshake(sock, 0);

    if (sock->ssl->handshake.server.async_resumption.session_data != NULL) {
        SSL_SESSION_free(sock->ssl->handshake.server.async_resumption.session_data);
        sock->ssl->handshake.server.async_resumption.session_data = NULL;
    }
}