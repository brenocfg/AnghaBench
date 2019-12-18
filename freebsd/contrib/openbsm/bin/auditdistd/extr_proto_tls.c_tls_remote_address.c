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
struct tls_ctx {scalar_t__ tls_magic; int tls_wait_called; int tls_side; char* tls_raddr; int /*<<< orphan*/ * tls_tcp; int /*<<< orphan*/ * tls_sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ABORT (char*,int) ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int /*<<< orphan*/  PJDLOG_VERIFY (int) ; 
 scalar_t__ TLS_CTX_MAGIC ; 
#define  TLS_SIDE_CLIENT 130 
#define  TLS_SIDE_SERVER_LISTEN 129 
#define  TLS_SIDE_SERVER_WORK 128 
 int /*<<< orphan*/  bcopy (char*,char*,int) ; 
 int /*<<< orphan*/  proto_remote_address (int /*<<< orphan*/ *,char*,size_t) ; 
 size_t strlcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void
tls_remote_address(const void *ctx, char *addr, size_t size)
{
	const struct tls_ctx *tlsctx = ctx;

	PJDLOG_ASSERT(tlsctx != NULL);
	PJDLOG_ASSERT(tlsctx->tls_magic == TLS_CTX_MAGIC);
	PJDLOG_ASSERT(tlsctx->tls_wait_called);

	switch (tlsctx->tls_side) {
	case TLS_SIDE_CLIENT:
		PJDLOG_ASSERT(tlsctx->tls_sock != NULL);

		PJDLOG_VERIFY(strlcpy(addr, "tls://N/A", size) < size);
		break;
	case TLS_SIDE_SERVER_WORK:
		PJDLOG_ASSERT(tlsctx->tls_sock != NULL);

		PJDLOG_VERIFY(strlcpy(addr, tlsctx->tls_raddr, size) < size);
		break;
	case TLS_SIDE_SERVER_LISTEN:
		PJDLOG_ASSERT(tlsctx->tls_tcp != NULL);

		proto_remote_address(tlsctx->tls_tcp, addr, size);
		PJDLOG_ASSERT(strncmp(addr, "tcp://", 6) == 0);
		/* Replace tcp:// prefix with tls:// */
		bcopy("tls://", addr, 6);
		break;
	default:
		PJDLOG_ABORT("Invalid side (%d).", tlsctx->tls_side);
	}
}