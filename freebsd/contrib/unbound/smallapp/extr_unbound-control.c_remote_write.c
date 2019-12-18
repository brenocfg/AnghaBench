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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 scalar_t__ SSL_write (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal_exit (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ send (int,char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_err (char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsa_strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
remote_write(SSL* ssl, int fd, const char* buf, size_t len)
{
	if(ssl) {
		if(SSL_write(ssl, buf, (int)len) <= 0)
			ssl_err("could not SSL_write");
	} else {
		if(send(fd, buf, len, 0) < (ssize_t)len) {
#ifndef USE_WINSOCK
			fatal_exit("could not send: %s", strerror(errno));
#else
			fatal_exit("could not send: %s", wsa_strerror(WSAGetLastError()));
#endif
		}
	}
}