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
typedef  scalar_t__ u16 ;
struct sae_data {TYPE_1__* tmp; int /*<<< orphan*/  peer_commit_scalar; } ;
struct TYPE_2__ {int /*<<< orphan*/  peer_commit_element_ecc; int /*<<< orphan*/  own_commit_element_ecc; scalar_t__ ec; int /*<<< orphan*/  peer_commit_element_ffc; int /*<<< orphan*/  own_commit_element_ffc; scalar_t__ dh; int /*<<< orphan*/  own_commit_scalar; } ;

/* Variables and functions */
 scalar_t__ SAE_SILENTLY_DISCARD ; 
 scalar_t__ WLAN_STATUS_SUCCESS ; 
 scalar_t__ WLAN_STATUS_UNSPECIFIED_FAILURE ; 
 int /*<<< orphan*/  WPA_GET_LE16 (int /*<<< orphan*/  const*) ; 
 scalar_t__ crypto_bignum_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_ec_point_cmp (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sae_group_allowed (struct sae_data*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ sae_parse_commit_element (struct sae_data*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 scalar_t__ sae_parse_commit_scalar (struct sae_data*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sae_parse_commit_token (struct sae_data*,int /*<<< orphan*/  const**,int /*<<< orphan*/  const*,int /*<<< orphan*/  const**,size_t*) ; 
 scalar_t__ sae_parse_password_identifier (struct sae_data*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

u16 sae_parse_commit(struct sae_data *sae, const u8 *data, size_t len,
		     const u8 **token, size_t *token_len, int *allowed_groups)
{
	const u8 *pos = data, *end = data + len;
	u16 res;

	/* Check Finite Cyclic Group */
	if (end - pos < 2)
		return WLAN_STATUS_UNSPECIFIED_FAILURE;
	res = sae_group_allowed(sae, allowed_groups, WPA_GET_LE16(pos));
	if (res != WLAN_STATUS_SUCCESS)
		return res;
	pos += 2;

	/* Optional Anti-Clogging Token */
	sae_parse_commit_token(sae, &pos, end, token, token_len);

	/* commit-scalar */
	res = sae_parse_commit_scalar(sae, &pos, end);
	if (res != WLAN_STATUS_SUCCESS)
		return res;

	/* commit-element */
	res = sae_parse_commit_element(sae, &pos, end);
	if (res != WLAN_STATUS_SUCCESS)
		return res;

	/* Optional Password Identifier element */
	res = sae_parse_password_identifier(sae, pos, end);
	if (res != WLAN_STATUS_SUCCESS)
		return res;

	/*
	 * Check whether peer-commit-scalar and PEER-COMMIT-ELEMENT are same as
	 * the values we sent which would be evidence of a reflection attack.
	 */
	if (!sae->tmp->own_commit_scalar ||
	    crypto_bignum_cmp(sae->tmp->own_commit_scalar,
			      sae->peer_commit_scalar) != 0 ||
	    (sae->tmp->dh &&
	     (!sae->tmp->own_commit_element_ffc ||
	      crypto_bignum_cmp(sae->tmp->own_commit_element_ffc,
				sae->tmp->peer_commit_element_ffc) != 0)) ||
	    (sae->tmp->ec &&
	     (!sae->tmp->own_commit_element_ecc ||
	      crypto_ec_point_cmp(sae->tmp->ec,
				  sae->tmp->own_commit_element_ecc,
				  sae->tmp->peer_commit_element_ecc) != 0)))
		return WLAN_STATUS_SUCCESS; /* scalars/elements are different */

	/*
	 * This is a reflection attack - return special value to trigger caller
	 * to silently discard the frame instead of replying with a specific
	 * status code.
	 */
	return SAE_SILENTLY_DISCARD;
}