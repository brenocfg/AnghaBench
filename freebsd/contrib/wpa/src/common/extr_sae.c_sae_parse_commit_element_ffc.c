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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sae_data {TYPE_1__* tmp; } ;
struct crypto_bignum {int dummy; } ;
typedef  int /*<<< orphan*/  one_bin ;
struct TYPE_2__ {int prime_len; int /*<<< orphan*/  prime; int /*<<< orphan*/  order; struct crypto_bignum* peer_commit_element_ffc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WLAN_STATUS_SUCCESS ; 
 int /*<<< orphan*/  WLAN_STATUS_UNSPECIFIED_FAILURE ; 
 scalar_t__ crypto_bignum_cmp (struct crypto_bignum*,struct crypto_bignum*) ; 
 int /*<<< orphan*/  crypto_bignum_deinit (struct crypto_bignum*,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_bignum_exptmod (struct crypto_bignum*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct crypto_bignum*) ; 
 struct crypto_bignum* crypto_bignum_init () ; 
 void* crypto_bignum_init_set (int const*,int) ; 
 scalar_t__ crypto_bignum_is_one (struct crypto_bignum*) ; 
 scalar_t__ crypto_bignum_is_zero (struct crypto_bignum*) ; 
 scalar_t__ crypto_bignum_sub (int /*<<< orphan*/ ,struct crypto_bignum*,struct crypto_bignum*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static u16 sae_parse_commit_element_ffc(struct sae_data *sae, const u8 **pos,
					const u8 *end)
{
	struct crypto_bignum *res, *one;
	const u8 one_bin[1] = { 0x01 };

	if (sae->tmp->prime_len > end - *pos) {
		wpa_printf(MSG_DEBUG, "SAE: Not enough data for "
			   "commit-element");
		return WLAN_STATUS_UNSPECIFIED_FAILURE;
	}
	wpa_hexdump(MSG_DEBUG, "SAE: Peer commit-element", *pos,
		    sae->tmp->prime_len);

	crypto_bignum_deinit(sae->tmp->peer_commit_element_ffc, 0);
	sae->tmp->peer_commit_element_ffc =
		crypto_bignum_init_set(*pos, sae->tmp->prime_len);
	if (sae->tmp->peer_commit_element_ffc == NULL)
		return WLAN_STATUS_UNSPECIFIED_FAILURE;
	/* 1 < element < p - 1 */
	res = crypto_bignum_init();
	one = crypto_bignum_init_set(one_bin, sizeof(one_bin));
	if (!res || !one ||
	    crypto_bignum_sub(sae->tmp->prime, one, res) ||
	    crypto_bignum_is_zero(sae->tmp->peer_commit_element_ffc) ||
	    crypto_bignum_is_one(sae->tmp->peer_commit_element_ffc) ||
	    crypto_bignum_cmp(sae->tmp->peer_commit_element_ffc, res) >= 0) {
		crypto_bignum_deinit(res, 0);
		crypto_bignum_deinit(one, 0);
		wpa_printf(MSG_DEBUG, "SAE: Invalid peer element");
		return WLAN_STATUS_UNSPECIFIED_FAILURE;
	}
	crypto_bignum_deinit(one, 0);

	/* scalar-op(r, ELEMENT) = 1 modulo p */
	if (crypto_bignum_exptmod(sae->tmp->peer_commit_element_ffc,
				  sae->tmp->order, sae->tmp->prime, res) < 0 ||
	    !crypto_bignum_is_one(res)) {
		wpa_printf(MSG_DEBUG, "SAE: Invalid peer element (scalar-op)");
		crypto_bignum_deinit(res, 0);
		return WLAN_STATUS_UNSPECIFIED_FAILURE;
	}
	crypto_bignum_deinit(res, 0);

	*pos += sae->tmp->prime_len;

	return WLAN_STATUS_SUCCESS;
}