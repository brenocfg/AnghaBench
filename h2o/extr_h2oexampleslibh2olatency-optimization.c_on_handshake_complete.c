#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_socket_t ;
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 int /*<<< orphan*/  client_on_read_first ; 
 int /*<<< orphan*/  client_on_write_complete ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  h2o_socket_close (int /*<<< orphan*/ *) ; 
 char const* h2o_socket_error_ssl_cert_name_mismatch ; 
 int /*<<< orphan*/  h2o_socket_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_write (int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ mode_server ; 
 int /*<<< orphan*/  server_on_read_first ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void on_handshake_complete(h2o_socket_t *sock, const char *err)
{
    if (err != NULL && err != h2o_socket_error_ssl_cert_name_mismatch) {
        /* TLS handshake failed */
        fprintf(stderr, "TLS handshake failure:%s\n", err);
        ERR_print_errors_fp(stderr);
        h2o_socket_close(sock);
        exit(1);
        return;
    }

    if (mode_server) {
        h2o_socket_read_start(sock, server_on_read_first);
    } else {
        h2o_iovec_t buf = {H2O_STRLIT("0")};
        h2o_socket_write(sock, &buf, 1, client_on_write_complete);
        h2o_socket_read_start(sock, client_on_read_first);
    }
}