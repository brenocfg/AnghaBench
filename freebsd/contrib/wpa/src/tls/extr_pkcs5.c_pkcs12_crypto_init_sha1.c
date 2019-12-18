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
struct pkcs5_params {scalar_t__ alg; int /*<<< orphan*/  iter_count; int /*<<< orphan*/  salt_len; int /*<<< orphan*/  salt; } ;
struct crypto_cipher {int dummy; } ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  iv ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_CIPHER_ALG_3DES ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  PKCS12_ID_ENC ; 
 int /*<<< orphan*/  PKCS12_ID_IV ; 
 scalar_t__ PKCS5_ALG_SHA1_3DES_CBC ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ *,char const) ; 
 struct crypto_cipher* crypto_cipher_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (int) ; 
 size_t os_strlen (char const*) ; 
 scalar_t__ pkcs12_key_gen (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct crypto_cipher *
pkcs12_crypto_init_sha1(struct pkcs5_params *params, const char *passwd)
{
	unsigned int i;
	u8 *pw;
	size_t pw_len;
	u8 key[24];
	u8 iv[8];

	if (params->alg != PKCS5_ALG_SHA1_3DES_CBC)
		return NULL;

	pw_len = passwd ? os_strlen(passwd) : 0;
	pw = os_malloc(2 * (pw_len + 1));
	if (!pw)
		return NULL;
	if (pw_len) {
		for (i = 0; i <= pw_len; i++)
			WPA_PUT_BE16(&pw[2 * i], passwd[i]);
		pw_len = 2 * (pw_len + 1);
	}

	if (pkcs12_key_gen(pw, pw_len, params->salt, params->salt_len,
			   PKCS12_ID_ENC, params->iter_count,
			   sizeof(key), key) < 0 ||
	    pkcs12_key_gen(pw, pw_len, params->salt, params->salt_len,
			   PKCS12_ID_IV, params->iter_count,
			   sizeof(iv), iv) < 0) {
		os_free(pw);
		return NULL;
	}

	os_free(pw);

	wpa_hexdump_key(MSG_DEBUG, "PKCS #12: DES key", key, sizeof(key));
	wpa_hexdump_key(MSG_DEBUG, "PKCS #12: DES IV", iv, sizeof(iv));

	return crypto_cipher_init(CRYPTO_CIPHER_ALG_3DES, iv, key, sizeof(key));
}