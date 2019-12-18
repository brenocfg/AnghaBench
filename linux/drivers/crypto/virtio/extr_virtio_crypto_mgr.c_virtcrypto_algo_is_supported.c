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
typedef  unsigned int uint32_t ;
struct virtio_crypto {unsigned int crypto_services; unsigned int cipher_algo_l; unsigned int cipher_algo_h; unsigned int hash_algo; unsigned int mac_algo_l; unsigned int mac_algo_h; unsigned int aead_algo; } ;

/* Variables and functions */
#define  VIRTIO_CRYPTO_SERVICE_AEAD 131 
#define  VIRTIO_CRYPTO_SERVICE_CIPHER 130 
#define  VIRTIO_CRYPTO_SERVICE_HASH 129 
#define  VIRTIO_CRYPTO_SERVICE_MAC 128 

bool virtcrypto_algo_is_supported(struct virtio_crypto *vcrypto,
				  uint32_t service,
				  uint32_t algo)
{
	uint32_t service_mask = 1u << service;
	uint32_t algo_mask = 0;
	bool low = true;

	if (algo > 31) {
		algo -= 32;
		low = false;
	}

	if (!(vcrypto->crypto_services & service_mask))
		return false;

	switch (service) {
	case VIRTIO_CRYPTO_SERVICE_CIPHER:
		if (low)
			algo_mask = vcrypto->cipher_algo_l;
		else
			algo_mask = vcrypto->cipher_algo_h;
		break;

	case VIRTIO_CRYPTO_SERVICE_HASH:
		algo_mask = vcrypto->hash_algo;
		break;

	case VIRTIO_CRYPTO_SERVICE_MAC:
		if (low)
			algo_mask = vcrypto->mac_algo_l;
		else
			algo_mask = vcrypto->mac_algo_h;
		break;

	case VIRTIO_CRYPTO_SERVICE_AEAD:
		algo_mask = vcrypto->aead_algo;
		break;
	}

	if (!(algo_mask & (1u << algo)))
		return false;

	return true;
}