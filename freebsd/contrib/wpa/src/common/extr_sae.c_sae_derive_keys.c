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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  u8 ;
struct sae_data {int /*<<< orphan*/ * pmk; TYPE_1__* tmp; int /*<<< orphan*/ * pmkid; int /*<<< orphan*/  peer_commit_scalar; } ;
struct crypto_bignum {int dummy; } ;
typedef  int /*<<< orphan*/  null_key ;
typedef  int /*<<< orphan*/  keyseed ;
typedef  int /*<<< orphan*/  keys ;
struct TYPE_2__ {int /*<<< orphan*/ * kck; int /*<<< orphan*/  order_len; int /*<<< orphan*/  order; int /*<<< orphan*/  own_commit_scalar; int /*<<< orphan*/  prime_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int SAE_KCK_LEN ; 
 int SAE_KEYSEED_KEY_LEN ; 
 int SAE_MAX_PRIME_LEN ; 
 int SAE_PMKID_LEN ; 
 int SAE_PMK_LEN ; 
 int SHA256_MAC_LEN ; 
 int /*<<< orphan*/  crypto_bignum_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct crypto_bignum*) ; 
 int /*<<< orphan*/  crypto_bignum_deinit (struct crypto_bignum*,int /*<<< orphan*/ ) ; 
 struct crypto_bignum* crypto_bignum_init () ; 
 int /*<<< orphan*/  crypto_bignum_mod (struct crypto_bignum*,int /*<<< orphan*/ ,struct crypto_bignum*) ; 
 int /*<<< orphan*/  crypto_bignum_to_bin (struct crypto_bignum*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hmac_sha256 (int /*<<< orphan*/ *,int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sha256_prf (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int sae_derive_keys(struct sae_data *sae, const u8 *k)
{
	u8 null_key[SAE_KEYSEED_KEY_LEN], val[SAE_MAX_PRIME_LEN];
	u8 keyseed[SHA256_MAC_LEN];
	u8 keys[SAE_KCK_LEN + SAE_PMK_LEN];
	struct crypto_bignum *tmp;
	int ret = -1;

	tmp = crypto_bignum_init();
	if (tmp == NULL)
		goto fail;

	/* keyseed = H(<0>32, k)
	 * KCK || PMK = KDF-512(keyseed, "SAE KCK and PMK",
	 *                      (commit-scalar + peer-commit-scalar) modulo r)
	 * PMKID = L((commit-scalar + peer-commit-scalar) modulo r, 0, 128)
	 */

	os_memset(null_key, 0, sizeof(null_key));
	hmac_sha256(null_key, sizeof(null_key), k, sae->tmp->prime_len,
		    keyseed);
	wpa_hexdump_key(MSG_DEBUG, "SAE: keyseed", keyseed, sizeof(keyseed));

	crypto_bignum_add(sae->tmp->own_commit_scalar, sae->peer_commit_scalar,
			  tmp);
	crypto_bignum_mod(tmp, sae->tmp->order, tmp);
	/* IEEE Std 802.11-2016 is not exactly clear on the encoding of the bit
	 * string that is needed for KCK, PMK, and PMKID derivation, but it
	 * seems to make most sense to encode the
	 * (commit-scalar + peer-commit-scalar) mod r part as a bit string by
	 * zero padding it from left to the length of the order (in full
	 * octets). */
	crypto_bignum_to_bin(tmp, val, sizeof(val), sae->tmp->order_len);
	wpa_hexdump(MSG_DEBUG, "SAE: PMKID", val, SAE_PMKID_LEN);
	if (sha256_prf(keyseed, sizeof(keyseed), "SAE KCK and PMK",
		       val, sae->tmp->order_len, keys, sizeof(keys)) < 0)
		goto fail;
	os_memset(keyseed, 0, sizeof(keyseed));
	os_memcpy(sae->tmp->kck, keys, SAE_KCK_LEN);
	os_memcpy(sae->pmk, keys + SAE_KCK_LEN, SAE_PMK_LEN);
	os_memcpy(sae->pmkid, val, SAE_PMKID_LEN);
	os_memset(keys, 0, sizeof(keys));
	wpa_hexdump_key(MSG_DEBUG, "SAE: KCK", sae->tmp->kck, SAE_KCK_LEN);
	wpa_hexdump_key(MSG_DEBUG, "SAE: PMK", sae->pmk, SAE_PMK_LEN);

	ret = 0;
fail:
	crypto_bignum_deinit(tmp, 0);
	return ret;
}