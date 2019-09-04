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
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  ptls_handshake_properties_t ;
typedef  int /*<<< orphan*/  ptls_context_t ;
typedef  int /*<<< orphan*/  on ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bind (int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle_connection (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ listen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run_server(struct sockaddr *sa, socklen_t salen, ptls_context_t *ctx, const char *input_file,
                      ptls_handshake_properties_t *hsprop, int request_key_update)
{
    int listen_fd, conn_fd, on = 1;

    if ((listen_fd = socket(sa->sa_family, SOCK_STREAM, 0)) == -1) {
        perror("socket(2) failed");
        return 1;
    }
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) != 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
        return 1;
    }
    if (bind(listen_fd, sa, salen) != 0) {
        perror("bind(2) failed");
        return 1;
    }
    if (listen(listen_fd, SOMAXCONN) != 0) {
        perror("listen(2) failed");
        return 1;
    }

    while (1) {
        if ((conn_fd = accept(listen_fd, NULL, 0)) != -1)
            handle_connection(conn_fd, ctx, NULL, input_file, hsprop, request_key_update);
    }

    return 0;
}