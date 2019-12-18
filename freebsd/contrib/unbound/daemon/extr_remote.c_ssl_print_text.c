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
typedef  int ssize_t ;
struct TYPE_3__ {int /*<<< orphan*/  fd; scalar_t__ ssl; } ;
typedef  TYPE_1__ RES ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  ERR_clear_error () ; 
 scalar_t__ SSL_ERROR_ZERO_RETURN ; 
 scalar_t__ SSL_get_error (scalar_t__,int) ; 
 int SSL_write (scalar_t__,char const*,int) ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  WSAGetLastError () ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  log_crypto_err (char*) ; 
 int /*<<< orphan*/  log_err (char*,int /*<<< orphan*/ ) ; 
 int send (int /*<<< orphan*/ ,char const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wsa_strerror (int /*<<< orphan*/ ) ; 

int
ssl_print_text(RES* res, const char* text)
{
	int r;
	if(!res) 
		return 0;
	if(res->ssl) {
		ERR_clear_error();
		if((r=SSL_write(res->ssl, text, (int)strlen(text))) <= 0) {
			if(SSL_get_error(res->ssl, r) == SSL_ERROR_ZERO_RETURN) {
				verbose(VERB_QUERY, "warning, in SSL_write, peer "
					"closed connection");
				return 0;
			}
			log_crypto_err("could not SSL_write");
			return 0;
		}
	} else {
		size_t at = 0;
		while(at < strlen(text)) {
			ssize_t r = send(res->fd, text+at, strlen(text)-at, 0);
			if(r == -1) {
				if(errno == EAGAIN || errno == EINTR)
					continue;
#ifndef USE_WINSOCK
				log_err("could not send: %s", strerror(errno));
#else
				log_err("could not send: %s", wsa_strerror(WSAGetLastError()));
#endif
				return 0;
			}
			at += r;
		}
	}
	return 1;
}