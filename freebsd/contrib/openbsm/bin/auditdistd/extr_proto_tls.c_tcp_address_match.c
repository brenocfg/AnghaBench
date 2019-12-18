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
struct tls_ctx {scalar_t__ tls_magic; int /*<<< orphan*/  tls_raddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 scalar_t__ TLS_CTX_MAGIC ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool
tcp_address_match(const void *ctx, const char *addr)
{
	const struct tls_ctx *tlsctx = ctx;

	PJDLOG_ASSERT(tlsctx != NULL);
	PJDLOG_ASSERT(tlsctx->tls_magic == TLS_CTX_MAGIC);

	return (strcmp(tlsctx->tls_raddr, addr) == 0);
}