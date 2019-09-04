#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ h2o_socket_t ;

/* Variables and functions */
 int exit_loop ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_close (TYPE_1__*) ; 
 int /*<<< orphan*/  h2o_socket_ssl_handshake (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_write (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host ; 
 int /*<<< orphan*/  on_handshake_complete ; 
 int /*<<< orphan*/  on_write ; 
 int /*<<< orphan*/ * ssl_ctx ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void on_connect(h2o_socket_t *sock, const char *err)
{
    if (err != NULL) {
        /* connection failed */
        fprintf(stderr, "failed to connect to host:%s\n", err);
        h2o_socket_close(sock);
        exit_loop = 1;
        return;
    }

    if (ssl_ctx != NULL) {
        h2o_socket_ssl_handshake(sock, ssl_ctx, host, h2o_iovec_init(NULL, 0), on_handshake_complete);
    } else {
        h2o_socket_write(sock, sock->data, 1, on_write);
    }
}