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
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  fd; scalar_t__ ssl; } ;
typedef  TYPE_1__ RES ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 scalar_t__ SSL_ERROR_ZERO_RETURN ; 
 scalar_t__ SSL_get_error (scalar_t__,int) ; 
 int SSL_read (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  log_crypto_err (char*) ; 
 int /*<<< orphan*/  log_err (char*,int,...) ; 
 scalar_t__ recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  wsa_strerror (int /*<<< orphan*/ ) ; 

int
ssl_read_line(RES* res, char* buf, size_t max)
{
	int r;
	size_t len = 0;
	if(!res)
		return 0;
	while(len < max) {
		if(res->ssl) {
			ERR_clear_error();
			if((r=SSL_read(res->ssl, buf+len, 1)) <= 0) {
				if(SSL_get_error(res->ssl, r) == SSL_ERROR_ZERO_RETURN) {
					buf[len] = 0;
					return 1;
				}
				log_crypto_err("could not SSL_read");
				return 0;
			}
		} else {
			while(1) {
				ssize_t rr = recv(res->fd, buf+len, 1, 0);
				if(rr <= 0) {
					if(rr == 0) {
						buf[len] = 0;
						return 1;
					}
					if(errno == EINTR || errno == EAGAIN)
						continue;
#ifndef USE_WINSOCK
					log_err("could not recv: %s", strerror(errno));
#else
					log_err("could not recv: %s", wsa_strerror(WSAGetLastError()));
#endif
					return 0;
				}
				break;
			}
		}
		if(buf[len] == '\n') {
			/* return string without \n */
			buf[len] = 0;
			return 1;
		}
		len++;
	}
	buf[max-1] = 0;
	log_err("control line too long (%d): %s", (int)max, buf);
	return 0;
}