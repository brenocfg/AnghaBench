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
struct prng_context {int flags; } ;
struct crypto_rng {int dummy; } ;

/* Variables and functions */
 int DEFAULT_BLK_SZ ; 
 int DEFAULT_PRNG_KSZ ; 
 int EINVAL ; 
 int PRNG_NEED_RESET ; 
 struct prng_context* crypto_rng_ctx (struct crypto_rng*) ; 
 int /*<<< orphan*/  reset_prng_context (struct prng_context*,int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int cprng_reset(struct crypto_rng *tfm,
		       const u8 *seed, unsigned int slen)
{
	struct prng_context *prng = crypto_rng_ctx(tfm);
	const u8 *key = seed + DEFAULT_BLK_SZ;
	const u8 *dt = NULL;

	if (slen < DEFAULT_PRNG_KSZ + DEFAULT_BLK_SZ)
		return -EINVAL;

	if (slen >= (2 * DEFAULT_BLK_SZ + DEFAULT_PRNG_KSZ))
		dt = key + DEFAULT_PRNG_KSZ;

	reset_prng_context(prng, key, DEFAULT_PRNG_KSZ, seed, dt);

	if (prng->flags & PRNG_NEED_RESET)
		return -EINVAL;
	return 0;
}