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
typedef  int /*<<< orphan*/  DH ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 scalar_t__ DH_generate_key (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_get0_key (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_get0_pqg (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DH_set_length (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int INT_MAX ; 
 int /*<<< orphan*/  MINIMUM (int,int) ; 
 int SSH_ERR_INVALID_ARGUMENT ; 
 int SSH_ERR_INVALID_FORMAT ; 
 int SSH_ERR_LIBCRYPTO_ERROR ; 
 int /*<<< orphan*/  dh_pub_is_valid (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 

int
dh_gen_key(DH *dh, int need)
{
	int pbits;
	const BIGNUM *dh_p, *pub_key;

	DH_get0_pqg(dh, &dh_p, NULL, NULL);

	if (need < 0 || dh_p == NULL ||
	    (pbits = BN_num_bits(dh_p)) <= 0 ||
	    need > INT_MAX / 2 || 2 * need > pbits)
		return SSH_ERR_INVALID_ARGUMENT;
	if (need < 256)
		need = 256;
	/*
	 * Pollard Rho, Big step/Little Step attacks are O(sqrt(n)),
	 * so double requested need here.
	 */
	if (!DH_set_length(dh, MINIMUM(need * 2, pbits - 1)))
		return SSH_ERR_LIBCRYPTO_ERROR;

	if (DH_generate_key(dh) == 0)
		return SSH_ERR_LIBCRYPTO_ERROR;
	DH_get0_key(dh, &pub_key, NULL);
	if (!dh_pub_is_valid(dh, pub_key))
		return SSH_ERR_INVALID_FORMAT;
	return 0;
}