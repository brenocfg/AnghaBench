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
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_clear_error () ; 
 scalar_t__ SSL_ERROR_ZERO_RETURN ; 
 scalar_t__ SSL_get_error (int /*<<< orphan*/ *,int) ; 
 int SSL_read (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fatal_exit (char*,int /*<<< orphan*/ ) ; 
 size_t recv (int,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_err (char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wsa_strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
remote_read(SSL* ssl, int fd, char* buf, size_t len)
{
	if(ssl) {
		int r;
		ERR_clear_error();
		if((r = SSL_read(ssl, buf, (int)len-1)) <= 0) {
			if(SSL_get_error(ssl, r) == SSL_ERROR_ZERO_RETURN) {
				/* EOF */
				return 0;
			}
			ssl_err("could not SSL_read");
		}
		buf[r] = 0;
	} else {
		ssize_t rr = recv(fd, buf, len-1, 0);
		if(rr <= 0) {
			if(rr == 0) {
				/* EOF */
				return 0;
			}
#ifndef USE_WINSOCK
			fatal_exit("could not recv: %s", strerror(errno));
#else
			fatal_exit("could not recv: %s", wsa_strerror(WSAGetLastError()));
#endif
		}
		buf[rr] = 0;
	}
	return 1;
}