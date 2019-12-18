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
struct pkcs5_params {scalar_t__ alg; size_t salt_len; unsigned int iter_count; int /*<<< orphan*/ * salt; } ;
struct crypto_cipher {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_CIPHER_ALG_DES ; 
 int MD5_MAC_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ PKCS5_ALG_MD5_DES_CBC ; 
 scalar_t__ PKCS5_ALG_PBES2 ; 
 scalar_t__ PKCS5_ALG_SHA1_3DES_CBC ; 
 struct crypto_cipher* crypto_cipher_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ md5_vector (int,int /*<<< orphan*/  const**,size_t*,int /*<<< orphan*/ *) ; 
 size_t os_strlen (char const*) ; 
 struct crypto_cipher* pkcs12_crypto_init_sha1 (struct pkcs5_params*,char const*) ; 
 struct crypto_cipher* pkcs5_crypto_init_pbes2 (struct pkcs5_params*,char const*) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct crypto_cipher * pkcs5_crypto_init(struct pkcs5_params *params,
						const char *passwd)
{
	unsigned int i;
	u8 hash[MD5_MAC_LEN];
	const u8 *addr[2];
	size_t len[2];

	if (params->alg == PKCS5_ALG_PBES2)
		return pkcs5_crypto_init_pbes2(params, passwd);

	if (params->alg == PKCS5_ALG_SHA1_3DES_CBC)
		return pkcs12_crypto_init_sha1(params, passwd);

	if (params->alg != PKCS5_ALG_MD5_DES_CBC)
		return NULL;

	addr[0] = (const u8 *) passwd;
	len[0] = os_strlen(passwd);
	addr[1] = params->salt;
	len[1] = params->salt_len;
	if (md5_vector(2, addr, len, hash) < 0)
		return NULL;
	addr[0] = hash;
	len[0] = MD5_MAC_LEN;
	for (i = 1; i < params->iter_count; i++) {
		if (md5_vector(1, addr, len, hash) < 0)
			return NULL;
	}
	/* TODO: DES key parity bits(?) */
	wpa_hexdump_key(MSG_DEBUG, "PKCS #5: DES key", hash, 8);
	wpa_hexdump_key(MSG_DEBUG, "PKCS #5: DES IV", hash + 8, 8);

	return crypto_cipher_init(CRYPTO_CIPHER_ALG_DES, hash + 8, hash, 8);
}