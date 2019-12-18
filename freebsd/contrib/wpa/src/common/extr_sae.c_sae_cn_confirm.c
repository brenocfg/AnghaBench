#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct sae_data {TYPE_1__* tmp; } ;
struct crypto_bignum {int dummy; } ;
typedef  int /*<<< orphan*/  scalar_b2 ;
typedef  int /*<<< orphan*/  scalar_b1 ;
struct TYPE_2__ {size_t prime_len; int /*<<< orphan*/  kck; } ;

/* Variables and functions */
 int SAE_MAX_PRIME_LEN ; 
 int /*<<< orphan*/  crypto_bignum_to_bin (struct crypto_bignum const*,int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  hmac_sha256_vector (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sae_cn_confirm(struct sae_data *sae, const u8 *sc,
			   const struct crypto_bignum *scalar1,
			   const u8 *element1, size_t element1_len,
			   const struct crypto_bignum *scalar2,
			   const u8 *element2, size_t element2_len,
			   u8 *confirm)
{
	const u8 *addr[5];
	size_t len[5];
	u8 scalar_b1[SAE_MAX_PRIME_LEN], scalar_b2[SAE_MAX_PRIME_LEN];

	/* Confirm
	 * CN(key, X, Y, Z, ...) =
	 *    HMAC-SHA256(key, D2OS(X) || D2OS(Y) || D2OS(Z) | ...)
	 * confirm = CN(KCK, send-confirm, commit-scalar, COMMIT-ELEMENT,
	 *              peer-commit-scalar, PEER-COMMIT-ELEMENT)
	 * verifier = CN(KCK, peer-send-confirm, peer-commit-scalar,
	 *               PEER-COMMIT-ELEMENT, commit-scalar, COMMIT-ELEMENT)
	 */
	addr[0] = sc;
	len[0] = 2;
	crypto_bignum_to_bin(scalar1, scalar_b1, sizeof(scalar_b1),
			     sae->tmp->prime_len);
	addr[1] = scalar_b1;
	len[1] = sae->tmp->prime_len;
	addr[2] = element1;
	len[2] = element1_len;
	crypto_bignum_to_bin(scalar2, scalar_b2, sizeof(scalar_b2),
			     sae->tmp->prime_len);
	addr[3] = scalar_b2;
	len[3] = sae->tmp->prime_len;
	addr[4] = element2;
	len[4] = element2_len;
	hmac_sha256_vector(sae->tmp->kck, sizeof(sae->tmp->kck), 5, addr, len,
			   confirm);
}