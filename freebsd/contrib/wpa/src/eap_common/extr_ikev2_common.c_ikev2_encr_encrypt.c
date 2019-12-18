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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_cipher {int dummy; } ;

/* Variables and functions */
 int CRYPTO_CIPHER_ALG_3DES ; 
 int CRYPTO_CIPHER_ALG_AES ; 
#define  ENCR_3DES 129 
#define  ENCR_AES_CBC 128 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  crypto_cipher_deinit (struct crypto_cipher*) ; 
 scalar_t__ crypto_cipher_encrypt (struct crypto_cipher*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,size_t) ; 
 struct crypto_cipher* crypto_cipher_init (int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

int ikev2_encr_encrypt(int alg, const u8 *key, size_t key_len, const u8 *iv,
		       const u8 *plain, u8 *crypt, size_t len)
{
	struct crypto_cipher *cipher;
	int encr_alg;

	switch (alg) {
	case ENCR_3DES:
		encr_alg = CRYPTO_CIPHER_ALG_3DES;
		break;
	case ENCR_AES_CBC:
		encr_alg = CRYPTO_CIPHER_ALG_AES;
		break;
	default:
		wpa_printf(MSG_DEBUG, "IKEV2: Unsupported encr alg %d", alg);
		return -1;
	}

	cipher = crypto_cipher_init(encr_alg, iv, key, key_len);
	if (cipher == NULL) {
		wpa_printf(MSG_INFO, "IKEV2: Failed to initialize cipher");
		return -1;
	}

	if (crypto_cipher_encrypt(cipher, plain, crypt, len) < 0) {
		wpa_printf(MSG_INFO, "IKEV2: Encryption failed");
		crypto_cipher_deinit(cipher);
		return -1;
	}
	crypto_cipher_deinit(cipher);

	return 0;
}