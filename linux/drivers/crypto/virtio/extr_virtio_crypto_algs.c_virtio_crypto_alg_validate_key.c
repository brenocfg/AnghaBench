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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
#define  AES_KEYSIZE_128 130 
#define  AES_KEYSIZE_192 129 
#define  AES_KEYSIZE_256 128 
 int EINVAL ; 
 int /*<<< orphan*/  VIRTIO_CRYPTO_CIPHER_AES_CBC ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 

__attribute__((used)) static int
virtio_crypto_alg_validate_key(int key_len, uint32_t *alg)
{
	switch (key_len) {
	case AES_KEYSIZE_128:
	case AES_KEYSIZE_192:
	case AES_KEYSIZE_256:
		*alg = VIRTIO_CRYPTO_CIPHER_AES_CBC;
		break;
	default:
		pr_err("virtio_crypto: Unsupported key length: %d\n",
			key_len);
		return -EINVAL;
	}
	return 0;
}