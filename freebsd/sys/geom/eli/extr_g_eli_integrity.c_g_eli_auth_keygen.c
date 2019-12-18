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
typedef  int /*<<< orphan*/  u_char ;
struct g_eli_softc {int /*<<< orphan*/  sc_akeyctx; } ;
typedef  int /*<<< orphan*/  offset ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  ctx ;
typedef  int /*<<< orphan*/  SHA256_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SHA256_Final (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA256_Update (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
g_eli_auth_keygen(struct g_eli_softc *sc, off_t offset, u_char *key)
{
	SHA256_CTX ctx;

	/* Copy precalculated SHA256 context. */
	bcopy(&sc->sc_akeyctx, &ctx, sizeof(ctx));
	SHA256_Update(&ctx, (uint8_t *)&offset, sizeof(offset));
	SHA256_Final(key, &ctx);
}