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
struct shash_desc {int dummy; } ;
struct sha1_state {unsigned int count; } ;
struct octeon_cop2_state {int dummy; } ;

/* Variables and functions */
 unsigned int SHA1_BLOCK_SIZE ; 
 int /*<<< orphan*/  __octeon_sha1_update (struct sha1_state*,int /*<<< orphan*/  const*,unsigned int) ; 
 int crypto_sha1_update (struct shash_desc*,int /*<<< orphan*/  const*,unsigned int) ; 
 int /*<<< orphan*/  octeon_crypto_disable (struct octeon_cop2_state*,unsigned long) ; 
 unsigned long octeon_crypto_enable (struct octeon_cop2_state*) ; 
 int /*<<< orphan*/  octeon_sha1_read_hash (struct sha1_state*) ; 
 int /*<<< orphan*/  octeon_sha1_store_hash (struct sha1_state*) ; 
 struct sha1_state* shash_desc_ctx (struct shash_desc*) ; 

__attribute__((used)) static int octeon_sha1_update(struct shash_desc *desc, const u8 *data,
			unsigned int len)
{
	struct sha1_state *sctx = shash_desc_ctx(desc);
	struct octeon_cop2_state state;
	unsigned long flags;

	/*
	 * Small updates never reach the crypto engine, so the generic sha1 is
	 * faster because of the heavyweight octeon_crypto_enable() /
	 * octeon_crypto_disable().
	 */
	if ((sctx->count % SHA1_BLOCK_SIZE) + len < SHA1_BLOCK_SIZE)
		return crypto_sha1_update(desc, data, len);

	flags = octeon_crypto_enable(&state);
	octeon_sha1_store_hash(sctx);

	__octeon_sha1_update(sctx, data, len);

	octeon_sha1_read_hash(sctx);
	octeon_crypto_disable(&state, flags);

	return 0;
}