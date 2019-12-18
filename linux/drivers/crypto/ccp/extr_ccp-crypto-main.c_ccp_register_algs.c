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

/* Variables and functions */
 int /*<<< orphan*/  aead_algs ; 
 int /*<<< orphan*/  aes_disable ; 
 int /*<<< orphan*/  akcipher_algs ; 
 int ccp_register_aes_aeads (int /*<<< orphan*/ *) ; 
 int ccp_register_aes_algs (int /*<<< orphan*/ *) ; 
 int ccp_register_aes_cmac_algs (int /*<<< orphan*/ *) ; 
 int ccp_register_aes_xts_algs (int /*<<< orphan*/ *) ; 
 int ccp_register_des3_algs (int /*<<< orphan*/ *) ; 
 int ccp_register_rsa_algs (int /*<<< orphan*/ *) ; 
 int ccp_register_sha_algs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cipher_algs ; 
 int /*<<< orphan*/  des3_disable ; 
 int /*<<< orphan*/  hash_algs ; 
 int /*<<< orphan*/  rsa_disable ; 
 int /*<<< orphan*/  sha_disable ; 

__attribute__((used)) static int ccp_register_algs(void)
{
	int ret;

	if (!aes_disable) {
		ret = ccp_register_aes_algs(&cipher_algs);
		if (ret)
			return ret;

		ret = ccp_register_aes_cmac_algs(&hash_algs);
		if (ret)
			return ret;

		ret = ccp_register_aes_xts_algs(&cipher_algs);
		if (ret)
			return ret;

		ret = ccp_register_aes_aeads(&aead_algs);
		if (ret)
			return ret;
	}

	if (!des3_disable) {
		ret = ccp_register_des3_algs(&cipher_algs);
		if (ret)
			return ret;
	}

	if (!sha_disable) {
		ret = ccp_register_sha_algs(&hash_algs);
		if (ret)
			return ret;
	}

	if (!rsa_disable) {
		ret = ccp_register_rsa_algs(&akcipher_algs);
		if (ret)
			return ret;
	}

	return 0;
}