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
struct swcr_session {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CRYPTOCAP_F_SOFTWARE ; 
 int CRYPTOCAP_F_SYNC ; 
 int /*<<< orphan*/  CRYPTO_3DES_CBC ; 
 int /*<<< orphan*/  CRYPTO_AES_128_NIST_GMAC ; 
 int /*<<< orphan*/  CRYPTO_AES_192_NIST_GMAC ; 
 int /*<<< orphan*/  CRYPTO_AES_256_NIST_GMAC ; 
 int /*<<< orphan*/  CRYPTO_AES_CCM_16 ; 
 int /*<<< orphan*/  CRYPTO_AES_CCM_CBC_MAC ; 
 int /*<<< orphan*/  CRYPTO_AES_ICM ; 
 int /*<<< orphan*/  CRYPTO_AES_NIST_GCM_16 ; 
 int /*<<< orphan*/  CRYPTO_AES_NIST_GMAC ; 
 int /*<<< orphan*/  CRYPTO_AES_XTS ; 
 int /*<<< orphan*/  CRYPTO_BLAKE2B ; 
 int /*<<< orphan*/  CRYPTO_BLAKE2S ; 
 int /*<<< orphan*/  CRYPTO_BLF_CBC ; 
 int /*<<< orphan*/  CRYPTO_CAMELLIA_CBC ; 
 int /*<<< orphan*/  CRYPTO_CAST_CBC ; 
 int /*<<< orphan*/  CRYPTO_CHACHA20 ; 
 int /*<<< orphan*/  CRYPTO_DEFLATE_COMP ; 
 int /*<<< orphan*/  CRYPTO_DES_CBC ; 
 int /*<<< orphan*/  CRYPTO_MD5 ; 
 int /*<<< orphan*/  CRYPTO_MD5_HMAC ; 
 int /*<<< orphan*/  CRYPTO_MD5_KPDK ; 
 int /*<<< orphan*/  CRYPTO_NULL_CBC ; 
 int /*<<< orphan*/  CRYPTO_NULL_HMAC ; 
 int /*<<< orphan*/  CRYPTO_POLY1305 ; 
 int /*<<< orphan*/  CRYPTO_RIJNDAEL128_CBC ; 
 int /*<<< orphan*/  CRYPTO_RIPEMD160_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA1 ; 
 int /*<<< orphan*/  CRYPTO_SHA1_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA1_KPDK ; 
 int /*<<< orphan*/  CRYPTO_SHA2_224 ; 
 int /*<<< orphan*/  CRYPTO_SHA2_224_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA2_256 ; 
 int /*<<< orphan*/  CRYPTO_SHA2_256_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA2_384 ; 
 int /*<<< orphan*/  CRYPTO_SHA2_384_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SHA2_512 ; 
 int /*<<< orphan*/  CRYPTO_SHA2_512_HMAC ; 
 int /*<<< orphan*/  CRYPTO_SKIPJACK_CBC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HMAC_IPAD_VAL ; 
 int /*<<< orphan*/  HMAC_MAX_BLOCK_LEN ; 
 int /*<<< orphan*/  HMAC_OPAD_VAL ; 
 int /*<<< orphan*/  REGISTER (int /*<<< orphan*/ ) ; 
 scalar_t__ crypto_get_driverid (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hmac_ipad_buffer ; 
 int /*<<< orphan*/  hmac_opad_buffer ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ swcr_id ; 

__attribute__((used)) static int
swcr_attach(device_t dev)
{
	memset(hmac_ipad_buffer, HMAC_IPAD_VAL, HMAC_MAX_BLOCK_LEN);
	memset(hmac_opad_buffer, HMAC_OPAD_VAL, HMAC_MAX_BLOCK_LEN);

	swcr_id = crypto_get_driverid(dev, sizeof(struct swcr_session),
			CRYPTOCAP_F_SOFTWARE | CRYPTOCAP_F_SYNC);
	if (swcr_id < 0) {
		device_printf(dev, "cannot initialize!");
		return ENOMEM;
	}
#define	REGISTER(alg) \
	crypto_register(swcr_id, alg, 0,0)
	REGISTER(CRYPTO_DES_CBC);
	REGISTER(CRYPTO_3DES_CBC);
	REGISTER(CRYPTO_BLF_CBC);
	REGISTER(CRYPTO_CAST_CBC);
	REGISTER(CRYPTO_SKIPJACK_CBC);
	REGISTER(CRYPTO_NULL_CBC);
	REGISTER(CRYPTO_MD5_HMAC);
	REGISTER(CRYPTO_SHA1_HMAC);
	REGISTER(CRYPTO_SHA2_224_HMAC);
	REGISTER(CRYPTO_SHA2_256_HMAC);
	REGISTER(CRYPTO_SHA2_384_HMAC);
	REGISTER(CRYPTO_SHA2_512_HMAC);
	REGISTER(CRYPTO_RIPEMD160_HMAC);
	REGISTER(CRYPTO_NULL_HMAC);
	REGISTER(CRYPTO_MD5_KPDK);
	REGISTER(CRYPTO_SHA1_KPDK);
	REGISTER(CRYPTO_MD5);
	REGISTER(CRYPTO_SHA1);
	REGISTER(CRYPTO_SHA2_224);
	REGISTER(CRYPTO_SHA2_256);
	REGISTER(CRYPTO_SHA2_384);
	REGISTER(CRYPTO_SHA2_512);
	REGISTER(CRYPTO_RIJNDAEL128_CBC);
	REGISTER(CRYPTO_AES_XTS);
	REGISTER(CRYPTO_AES_ICM);
	REGISTER(CRYPTO_AES_NIST_GCM_16);
	REGISTER(CRYPTO_AES_NIST_GMAC);
	REGISTER(CRYPTO_AES_128_NIST_GMAC);
	REGISTER(CRYPTO_AES_192_NIST_GMAC);
	REGISTER(CRYPTO_AES_256_NIST_GMAC);
 	REGISTER(CRYPTO_CAMELLIA_CBC);
	REGISTER(CRYPTO_DEFLATE_COMP);
	REGISTER(CRYPTO_BLAKE2B);
	REGISTER(CRYPTO_BLAKE2S);
	REGISTER(CRYPTO_CHACHA20);
	REGISTER(CRYPTO_AES_CCM_16);
	REGISTER(CRYPTO_AES_CCM_CBC_MAC);
	REGISTER(CRYPTO_POLY1305);
#undef REGISTER

	return 0;
}