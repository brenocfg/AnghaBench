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
struct pkcs5_params {scalar_t__ enc_alg; int iv_len; int salt_len; int /*<<< orphan*/  iv; int /*<<< orphan*/  iter_count; int /*<<< orphan*/  salt; } ;
struct crypto_cipher {int dummy; } ;
typedef  int /*<<< orphan*/  key ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_CIPHER_ALG_3DES ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ PBES2_ENC_ALG_DES_EDE3_CBC ; 
 struct crypto_cipher* crypto_cipher_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_strlen (char const*) ; 
 scalar_t__ pbkdf2_sha1 (char const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii_key (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct crypto_cipher *
pkcs5_crypto_init_pbes2(struct pkcs5_params *params, const char *passwd)
{
	u8 key[24];

	if (params->enc_alg != PBES2_ENC_ALG_DES_EDE3_CBC ||
	    params->iv_len != 8)
		return NULL;

	wpa_hexdump_ascii_key(MSG_DEBUG, "PKCS #5: PBES2 password for PBKDF2",
			      passwd, os_strlen(passwd));
	wpa_hexdump(MSG_DEBUG, "PKCS #5: PBES2 salt for PBKDF2",
		    params->salt, params->salt_len);
	wpa_printf(MSG_DEBUG, "PKCS #5: PBES2 PBKDF2 iterations: %u",
		   params->iter_count);
	if (pbkdf2_sha1(passwd, params->salt, params->salt_len,
			params->iter_count, key, sizeof(key)) < 0)
		return NULL;
	wpa_hexdump_key(MSG_DEBUG, "PKCS #5: DES EDE3 key", key, sizeof(key));
	wpa_hexdump(MSG_DEBUG, "PKCS #5: DES IV", params->iv, params->iv_len);

	return crypto_cipher_init(CRYPTO_CIPHER_ALG_3DES, params->iv,
				  key, sizeof(key));
}