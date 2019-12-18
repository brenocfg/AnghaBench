#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_url_t ;
struct TYPE_15__ {int /*<<< orphan*/ * ssl; } ;
typedef  TYPE_2__ h2o_socket_t ;
struct TYPE_16__ {scalar_t__ len; int /*<<< orphan*/  base; } ;
typedef  TYPE_3__ h2o_iovec_t ;
struct TYPE_17__ {TYPE_1__* connpool; int /*<<< orphan*/ * _connect_req; int /*<<< orphan*/  _timeout; } ;
typedef  TYPE_4__ h2o_httpclient_t ;
struct TYPE_14__ {int /*<<< orphan*/  socketpool; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_httpclient__h1_on_connect (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_httpclient__h2_on_connect (TYPE_4__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 char const* h2o_httpclient_error_unknown_alpn_protocol ; 
 scalar_t__ h2o_memis (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__ h2o_socket_ssl_get_selected_protocol (TYPE_2__*) ; 
 int /*<<< orphan*/  h2o_socketpool_detach (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  h2o_timer_unlink (int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  on_connect_error (TYPE_4__*,char const*) ; 

__attribute__((used)) static void on_pool_connect(h2o_socket_t *sock, const char *errstr, void *data, h2o_url_t *origin)
{
    h2o_httpclient_t *client = data;

    h2o_timer_unlink(&client->_timeout);

    client->_connect_req = NULL;

    if (sock == NULL) {
        assert(errstr != NULL);
        on_connect_error(client, errstr);
        return;
    }

    h2o_iovec_t alpn_proto;
    if (sock->ssl == NULL || (alpn_proto = h2o_socket_ssl_get_selected_protocol(sock)).len == 0) {
        h2o_httpclient__h1_on_connect(client, sock, origin);
    } else {
        if (h2o_memis(alpn_proto.base, alpn_proto.len, H2O_STRLIT("h2"))) {
            /* detach this socket from the socketpool to count the number of h1 connections correctly */
            h2o_socketpool_detach(client->connpool->socketpool, sock);
            h2o_httpclient__h2_on_connect(client, sock, origin);
        } else if (memcmp(alpn_proto.base, "http/1.1", alpn_proto.len) == 0) {
            h2o_httpclient__h1_on_connect(client, sock, origin);
        } else {
            on_connect_error(client, h2o_httpclient_error_unknown_alpn_protocol);
        }
    }
}