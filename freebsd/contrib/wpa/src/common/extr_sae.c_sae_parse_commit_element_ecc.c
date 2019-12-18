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
typedef  int /*<<< orphan*/  u16 ;
struct sae_data {TYPE_1__* tmp; } ;
typedef  int /*<<< orphan*/  prime ;
struct TYPE_2__ {int prime_len; int /*<<< orphan*/ * peer_commit_element_ecc; int /*<<< orphan*/  ec; int /*<<< orphan*/  prime; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int SAE_MAX_ECC_PRIME_LEN ; 
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WLAN_STATUS_UNSPECIFIED_FAILURE ; 
 scalar_t__ crypto_bignum_to_bin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  crypto_ec_point_deinit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * crypto_ec_point_from_bin (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  crypto_ec_point_is_on_curve (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static u16 sae_parse_commit_element_ecc(struct sae_data *sae, const u8 **pos,
					const u8 *end)
{
	u8 prime[SAE_MAX_ECC_PRIME_LEN];

	if (2 * sae->tmp->prime_len > end - *pos) {
		wpa_printf(MSG_DEBUG, "SAE: Not enough data for "
			   "commit-element");
		return WLAN_STATUS_UNSPECIFIED_FAILURE;
	}

	if (crypto_bignum_to_bin(sae->tmp->prime, prime, sizeof(prime),
				 sae->tmp->prime_len) < 0)
		return WLAN_STATUS_UNSPECIFIED_FAILURE;

	/* element x and y coordinates < p */
	if (os_memcmp(*pos, prime, sae->tmp->prime_len) >= 0 ||
	    os_memcmp(*pos + sae->tmp->prime_len, prime,
		      sae->tmp->prime_len) >= 0) {
		wpa_printf(MSG_DEBUG, "SAE: Invalid coordinates in peer "
			   "element");
		return WLAN_STATUS_UNSPECIFIED_FAILURE;
	}

	wpa_hexdump(MSG_DEBUG, "SAE: Peer commit-element(x)",
		    *pos, sae->tmp->prime_len);
	wpa_hexdump(MSG_DEBUG, "SAE: Peer commit-element(y)",
		    *pos + sae->tmp->prime_len, sae->tmp->prime_len);

	crypto_ec_point_deinit(sae->tmp->peer_commit_element_ecc, 0);
	sae->tmp->peer_commit_element_ecc =
		crypto_ec_point_from_bin(sae->tmp->ec, *pos);
	if (sae->tmp->peer_commit_element_ecc == NULL)
		return WLAN_STATUS_UNSPECIFIED_FAILURE;

	if (!crypto_ec_point_is_on_curve(sae->tmp->ec,
					 sae->tmp->peer_commit_element_ecc)) {
		wpa_printf(MSG_DEBUG, "SAE: Peer element is not on curve");
		return WLAN_STATUS_UNSPECIFIED_FAILURE;
	}

	*pos += 2 * sae->tmp->prime_len;

	return WLAN_STATUS_SUCCESS;
}