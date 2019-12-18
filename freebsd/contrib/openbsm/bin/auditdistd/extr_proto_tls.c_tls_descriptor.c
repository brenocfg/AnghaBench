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
struct tls_ctx {scalar_t__ tls_magic; int tls_side; int /*<<< orphan*/ * tls_tcp; int /*<<< orphan*/ * tls_sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ABORT (char*,int) ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ TLS_CTX_MAGIC ; 
#define  TLS_SIDE_CLIENT 130 
#define  TLS_SIDE_SERVER_LISTEN 129 
#define  TLS_SIDE_SERVER_WORK 128 
 int proto_descriptor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tls_descriptor(const void *ctx)
{
	const struct tls_ctx *tlsctx = ctx;

	PJDLOG_ASSERT(tlsctx != NULL);
	PJDLOG_ASSERT(tlsctx->tls_magic == TLS_CTX_MAGIC);

	switch (tlsctx->tls_side) {
	case TLS_SIDE_CLIENT:
	case TLS_SIDE_SERVER_WORK:
		PJDLOG_ASSERT(tlsctx->tls_sock != NULL);

		return (proto_descriptor(tlsctx->tls_sock));
	case TLS_SIDE_SERVER_LISTEN:
		PJDLOG_ASSERT(tlsctx->tls_tcp != NULL);

		return (proto_descriptor(tlsctx->tls_tcp));
	default:
		PJDLOG_ABORT("Invalid side (%d).", tlsctx->tls_side);
	}
}