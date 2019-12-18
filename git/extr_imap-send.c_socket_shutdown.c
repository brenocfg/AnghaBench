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
struct imap_socket {int /*<<< orphan*/ * fd; scalar_t__ ssl; } ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_free (scalar_t__) ; 
 int /*<<< orphan*/  SSL_shutdown (scalar_t__) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void socket_shutdown(struct imap_socket *sock)
{
#ifndef NO_OPENSSL
	if (sock->ssl) {
		SSL_shutdown(sock->ssl);
		SSL_free(sock->ssl);
	}
#endif
	close(sock->fd[0]);
	close(sock->fd[1]);
}