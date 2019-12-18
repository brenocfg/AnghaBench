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
typedef  int /*<<< orphan*/  RSA ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  RSA_get0_key (int /*<<< orphan*/  const*,int /*<<< orphan*/  const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SSH_ERR_KEY_LENGTH ; 
 scalar_t__ SSH_RSA_MINIMUM_MODULUS_SIZE ; 

__attribute__((used)) static int
check_rsa_length(const RSA *rsa)
{
	const BIGNUM *rsa_n;

	RSA_get0_key(rsa, &rsa_n, NULL, NULL);
	if (BN_num_bits(rsa_n) < SSH_RSA_MINIMUM_MODULUS_SIZE)
		return SSH_ERR_KEY_LENGTH;
	return 0;
}