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
struct tls_connection {int /*<<< orphan*/ * ssl; } ;
typedef  int /*<<< orphan*/  seed ;
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  WOLFSSL ;

/* Variables and functions */
 int RAN_LEN ; 
 int SEED_LEN ; 
 scalar_t__ WOLFSSL_TLSV1_2 ; 
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  forced_memzero (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int tls_prf_sha1_md5 (int /*<<< orphan*/ *,unsigned int,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tls_prf_sha256 (int /*<<< orphan*/ *,unsigned int,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int wolfSSL_GetHmacSize (int /*<<< orphan*/ *) ; 
 int wolfSSL_GetIVSize (int /*<<< orphan*/ *) ; 
 int wolfSSL_GetKeySize (int /*<<< orphan*/ *) ; 
 scalar_t__ wolfSSL_GetVersion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wolfSSL_get_keys (int /*<<< orphan*/ *,int /*<<< orphan*/ **,unsigned int*,int /*<<< orphan*/ **,unsigned int*,int /*<<< orphan*/ **,unsigned int*) ; 

int tls_connection_get_eap_fast_key(void *tls_ctx, struct tls_connection *conn,
				    u8 *out, size_t out_len)
{
	byte seed[SEED_LEN];
	int ret = -1;
	WOLFSSL *ssl;
	byte *tmp_out;
	byte *_out;
	int skip = 0;
	byte *master_key;
	unsigned int master_key_len;
	byte *server_random;
	unsigned int server_len;
	byte *client_random;
	unsigned int client_len;

	if (!conn || !conn->ssl)
		return -1;
	ssl = conn->ssl;

	skip = 2 * (wolfSSL_GetKeySize(ssl) + wolfSSL_GetHmacSize(ssl) +
		    wolfSSL_GetIVSize(ssl));

	tmp_out = os_malloc(skip + out_len);
	if (!tmp_out)
		return -1;
	_out = tmp_out;

	wolfSSL_get_keys(ssl, &master_key, &master_key_len, &server_random,
			 &server_len, &client_random, &client_len);
	os_memcpy(seed, server_random, RAN_LEN);
	os_memcpy(seed + RAN_LEN, client_random, RAN_LEN);

	if (wolfSSL_GetVersion(ssl) == WOLFSSL_TLSV1_2) {
		tls_prf_sha256(master_key, master_key_len,
			       "key expansion", seed, sizeof(seed),
			       _out, skip + out_len);
		ret = 0;
	} else {
		ret = tls_prf_sha1_md5(master_key, master_key_len,
				       "key expansion", seed, sizeof(seed),
				       _out, skip + out_len);
	}

	forced_memzero(master_key, master_key_len);
	if (ret == 0)
		os_memcpy(out, _out + skip, out_len);
	bin_clear_free(tmp_out, skip + out_len);

	return ret;
}