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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct shash_desc {int dummy; } ;
struct sha1_state {int count; int /*<<< orphan*/ * state; scalar_t__ buffer; } ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  ppc_sha1_clear_context (struct sha1_state*) ; 
 int /*<<< orphan*/  ppc_spe_sha1_transform (int /*<<< orphan*/ *,scalar_t__,int) ; 
 struct sha1_state* shash_desc_ctx (struct shash_desc*) ; 
 int /*<<< orphan*/  spe_begin () ; 
 int /*<<< orphan*/  spe_end () ; 

__attribute__((used)) static int ppc_spe_sha1_final(struct shash_desc *desc, u8 *out)
{
	struct sha1_state *sctx = shash_desc_ctx(desc);
	const unsigned int offset = sctx->count & 0x3f;
	char *p = (char *)sctx->buffer + offset;
	int padlen;
	__be64 *pbits = (__be64 *)(((char *)&sctx->buffer) + 56);
	__be32 *dst = (__be32 *)out;

	padlen = 55 - offset;
	*p++ = 0x80;

	spe_begin();

	if (padlen < 0) {
		memset(p, 0x00, padlen + sizeof (u64));
		ppc_spe_sha1_transform(sctx->state, sctx->buffer, 1);
		p = (char *)sctx->buffer;
		padlen = 56;
	}

	memset(p, 0, padlen);
	*pbits = cpu_to_be64(sctx->count << 3);
	ppc_spe_sha1_transform(sctx->state, sctx->buffer, 1);

	spe_end();

	dst[0] = cpu_to_be32(sctx->state[0]);
	dst[1] = cpu_to_be32(sctx->state[1]);
	dst[2] = cpu_to_be32(sctx->state[2]);
	dst[3] = cpu_to_be32(sctx->state[3]);
	dst[4] = cpu_to_be32(sctx->state[4]);

	ppc_sha1_clear_context(sctx);
	return 0;
}