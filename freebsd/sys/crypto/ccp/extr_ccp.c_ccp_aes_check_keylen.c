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
 int CRYPTO_AES_XTS ; 
 int EINVAL ; 

__attribute__((used)) static int
ccp_aes_check_keylen(int alg, int klen)
{

	switch (klen) {
	case 128:
	case 192:
		if (alg == CRYPTO_AES_XTS)
			return (EINVAL);
		break;
	case 256:
		break;
	case 512:
		if (alg != CRYPTO_AES_XTS)
			return (EINVAL);
		break;
	default:
		return (EINVAL);
	}
	return (0);
}