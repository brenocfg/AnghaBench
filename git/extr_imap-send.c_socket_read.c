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
struct imap_socket {int* fd; scalar_t__ ssl; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ SSL_read (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  socket_perror (char*,struct imap_socket*,scalar_t__) ; 
 scalar_t__ xread (int,char*,int) ; 

__attribute__((used)) static int socket_read(struct imap_socket *sock, char *buf, int len)
{
	ssize_t n;
#ifndef NO_OPENSSL
	if (sock->ssl)
		n = SSL_read(sock->ssl, buf, len);
	else
#endif
		n = xread(sock->fd[0], buf, len);
	if (n <= 0) {
		socket_perror("read", sock, n);
		close(sock->fd[0]);
		close(sock->fd[1]);
		sock->fd[0] = sock->fd[1] = -1;
	}
	return n;
}