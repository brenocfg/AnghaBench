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
typedef  int /*<<< orphan*/  u16 ;
struct tlsv1_record_layer {int /*<<< orphan*/  cipher_alg; int /*<<< orphan*/  iv_size; int /*<<< orphan*/  key_material_len; int /*<<< orphan*/  hash_size; int /*<<< orphan*/  hash_alg; int /*<<< orphan*/  cipher_suite; } ;
struct tls_cipher_suite {scalar_t__ hash; int /*<<< orphan*/  cipher; } ;
struct tls_cipher_data {int /*<<< orphan*/  alg; int /*<<< orphan*/  block_size; int /*<<< orphan*/  key_material; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_HASH_ALG_HMAC_MD5 ; 
 int /*<<< orphan*/  CRYPTO_HASH_ALG_HMAC_SHA1 ; 
 int /*<<< orphan*/  CRYPTO_HASH_ALG_HMAC_SHA256 ; 
 int /*<<< orphan*/  MD5_MAC_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  SHA1_MAC_LEN ; 
 int /*<<< orphan*/  SHA256_MAC_LEN ; 
 scalar_t__ TLS_HASH_MD5 ; 
 scalar_t__ TLS_HASH_SHA ; 
 scalar_t__ TLS_HASH_SHA256 ; 
 struct tls_cipher_data* tls_get_cipher_data (int /*<<< orphan*/ ) ; 
 struct tls_cipher_suite* tls_get_cipher_suite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int tlsv1_record_set_cipher_suite(struct tlsv1_record_layer *rl,
				  u16 cipher_suite)
{
	const struct tls_cipher_suite *suite;
	const struct tls_cipher_data *data;

	wpa_printf(MSG_DEBUG, "TLSv1: Selected cipher suite: 0x%04x",
		   cipher_suite);
	rl->cipher_suite = cipher_suite;

	suite = tls_get_cipher_suite(cipher_suite);
	if (suite == NULL)
		return -1;

	if (suite->hash == TLS_HASH_MD5) {
		rl->hash_alg = CRYPTO_HASH_ALG_HMAC_MD5;
		rl->hash_size = MD5_MAC_LEN;
	} else if (suite->hash == TLS_HASH_SHA) {
		rl->hash_alg = CRYPTO_HASH_ALG_HMAC_SHA1;
		rl->hash_size = SHA1_MAC_LEN;
	} else if (suite->hash == TLS_HASH_SHA256) {
		rl->hash_alg = CRYPTO_HASH_ALG_HMAC_SHA256;
		rl->hash_size = SHA256_MAC_LEN;
	}

	data = tls_get_cipher_data(suite->cipher);
	if (data == NULL)
		return -1;

	rl->key_material_len = data->key_material;
	rl->iv_size = data->block_size;
	rl->cipher_alg = data->alg;

	return 0;
}