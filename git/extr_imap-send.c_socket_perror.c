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
struct imap_socket {scalar_t__ ssl; } ;

/* Variables and functions */
#define  SSL_ERROR_NONE 129 
#define  SSL_ERROR_SYSCALL 128 
 int SSL_get_error (scalar_t__,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  ssl_socket_perror (char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void socket_perror(const char *func, struct imap_socket *sock, int ret)
{
#ifndef NO_OPENSSL
	if (sock->ssl) {
		int sslerr = SSL_get_error(sock->ssl, ret);
		switch (sslerr) {
		case SSL_ERROR_NONE:
			break;
		case SSL_ERROR_SYSCALL:
			perror("SSL_connect");
			break;
		default:
			ssl_socket_perror("SSL_connect");
			break;
		}
	} else
#endif
	{
		if (ret < 0)
			perror(func);
		else
			fprintf(stderr, "%s: unexpected EOF\n", func);
	}
}