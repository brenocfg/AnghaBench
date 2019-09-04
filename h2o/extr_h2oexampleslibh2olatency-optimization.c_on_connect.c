#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_socket_t ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  h2o_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_socket_ssl_handshake (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *)) ; 
 scalar_t__ mode_server ; 
 int /*<<< orphan*/  on_handshake_complete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ssl_ctx ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void on_connect(h2o_socket_t *sock, const char *err)
{
    if (err != NULL) {
        /* connection failed */
        fprintf(stderr, "failed to connect to host:%s\n", err);
        h2o_socket_close(sock);
        exit(1);
        return;
    }

    if (ssl_ctx != NULL) {
        h2o_socket_ssl_handshake(sock, ssl_ctx, mode_server ? NULL : "blahblah", h2o_iovec_init(NULL, 0), on_handshake_complete);
    } else {
        on_handshake_complete(sock, NULL);
    }
}