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
struct jitterentropy {int /*<<< orphan*/  jent_lock; int /*<<< orphan*/  entropy_collector; } ;
struct crypto_rng {int dummy; } ;

/* Variables and functions */
 struct jitterentropy* crypto_rng_ctx (struct crypto_rng*) ; 
 int jent_read_entropy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jent_kcapi_random(struct crypto_rng *tfm,
			     const u8 *src, unsigned int slen,
			     u8 *rdata, unsigned int dlen)
{
	struct jitterentropy *rng = crypto_rng_ctx(tfm);
	int ret = 0;

	spin_lock(&rng->jent_lock);
	ret = jent_read_entropy(rng->entropy_collector, rdata, dlen);
	spin_unlock(&rng->jent_lock);

	return ret;
}