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
typedef  int /*<<< orphan*/  uint8_t ;
struct tls_ctx {scalar_t__ tls_magic; scalar_t__ tls_side; int tls_wait_called; int /*<<< orphan*/ * tls_sock; } ;
typedef  int /*<<< orphan*/  connected ;

/* Variables and functions */
 int EINTR ; 
 int ENOBUFS ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  MSG_WAITALL ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ TLS_CTX_MAGIC ; 
 scalar_t__ TLS_SIDE_CLIENT ; 
 int errno ; 
 int /*<<< orphan*/  pjdlog_debug (int,char*) ; 
 int proto_descriptor (int /*<<< orphan*/ *) ; 
 int recv (int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int wait_for_fd (int,int) ; 

__attribute__((used)) static int
tls_connect_wait(void *ctx, int timeout)
{
	struct tls_ctx *tlsctx = ctx;
	int error, sockfd;
	uint8_t connected;

	PJDLOG_ASSERT(tlsctx != NULL);
	PJDLOG_ASSERT(tlsctx->tls_magic == TLS_CTX_MAGIC);
	PJDLOG_ASSERT(tlsctx->tls_side == TLS_SIDE_CLIENT);
	PJDLOG_ASSERT(tlsctx->tls_sock != NULL);
	PJDLOG_ASSERT(!tlsctx->tls_wait_called);
	PJDLOG_ASSERT(timeout >= 0);

	sockfd = proto_descriptor(tlsctx->tls_sock);
	error = wait_for_fd(sockfd, timeout);
	if (error != 0)
		return (error);

	for (;;) {
		switch (recv(sockfd, &connected, sizeof(connected),
		    MSG_WAITALL)) {
		case -1:
			if (errno == EINTR || errno == ENOBUFS)
				continue;
			error = errno;
			break;
		case 0:
			pjdlog_debug(1, "Connection terminated.");
			error = ENOTCONN;
			break;
		case 1:
			tlsctx->tls_wait_called = true;
			break;
		}
		break;
	}

	return (error);
}