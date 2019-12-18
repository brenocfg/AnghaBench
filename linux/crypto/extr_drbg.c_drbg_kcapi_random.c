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
struct drbg_string {int dummy; } ;
struct drbg_state {int dummy; } ;
struct crypto_rng {int dummy; } ;

/* Variables and functions */
 struct drbg_state* crypto_rng_ctx (struct crypto_rng*) ; 
 int drbg_generate_long (struct drbg_state*,int /*<<< orphan*/ *,unsigned int,struct drbg_string*) ; 
 int /*<<< orphan*/  drbg_string_fill (struct drbg_string*,int /*<<< orphan*/  const*,unsigned int) ; 

__attribute__((used)) static int drbg_kcapi_random(struct crypto_rng *tfm,
			     const u8 *src, unsigned int slen,
			     u8 *dst, unsigned int dlen)
{
	struct drbg_state *drbg = crypto_rng_ctx(tfm);
	struct drbg_string *addtl = NULL;
	struct drbg_string string;

	if (slen) {
		/* linked list variable is now local to allow modification */
		drbg_string_fill(&string, src, slen);
		addtl = &string;
	}

	return drbg_generate_long(drbg, dst, dlen, addtl);
}