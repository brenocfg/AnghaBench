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
typedef  unsigned char u8 ;
struct tls_connection {int /*<<< orphan*/ * ssl; } ;
typedef  int /*<<< orphan*/  server_random ;
typedef  int /*<<< orphan*/  master_key ;
typedef  int /*<<< orphan*/  client_random ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 int SSL3_RANDOM_SIZE ; 
 size_t SSL_SESSION_get_master_key (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  SSL_get_client_random (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  SSL_get_server_random (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/ * SSL_get_session (int /*<<< orphan*/ *) ; 
 char* SSL_get_version (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bin_clear_free (unsigned char*,int) ; 
 int /*<<< orphan*/  forced_memzero (unsigned char*,int) ; 
 int openssl_get_keyblock_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (unsigned char*) ; 
 unsigned char* os_malloc (int) ; 
 int /*<<< orphan*/  os_memcpy (unsigned char*,unsigned char*,size_t) ; 
 scalar_t__ os_strcmp (char const*,char*) ; 
 scalar_t__ tls_prf_sha1_md5 (unsigned char*,size_t,char*,unsigned char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  tls_prf_sha256 (unsigned char*,size_t,char*,unsigned char*,int,unsigned char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

int tls_connection_get_eap_fast_key(void *tls_ctx, struct tls_connection *conn,
				    u8 *out, size_t out_len)
{
#ifdef OPENSSL_NEED_EAP_FAST_PRF
	SSL *ssl;
	SSL_SESSION *sess;
	u8 *rnd;
	int ret = -1;
	int skip = 0;
	u8 *tmp_out = NULL;
	u8 *_out = out;
	unsigned char client_random[SSL3_RANDOM_SIZE];
	unsigned char server_random[SSL3_RANDOM_SIZE];
	unsigned char master_key[64];
	size_t master_key_len;
	const char *ver;

	/*
	 * TLS library did not support EAP-FAST key generation, so get the
	 * needed TLS session parameters and use an internal implementation of
	 * TLS PRF to derive the key.
	 */

	if (conn == NULL)
		return -1;
	ssl = conn->ssl;
	if (ssl == NULL)
		return -1;
	ver = SSL_get_version(ssl);
	sess = SSL_get_session(ssl);
	if (!ver || !sess)
		return -1;

	skip = openssl_get_keyblock_size(ssl);
	if (skip < 0)
		return -1;
	tmp_out = os_malloc(skip + out_len);
	if (!tmp_out)
		return -1;
	_out = tmp_out;

	rnd = os_malloc(2 * SSL3_RANDOM_SIZE);
	if (!rnd) {
		os_free(tmp_out);
		return -1;
	}

	SSL_get_client_random(ssl, client_random, sizeof(client_random));
	SSL_get_server_random(ssl, server_random, sizeof(server_random));
	master_key_len = SSL_SESSION_get_master_key(sess, master_key,
						    sizeof(master_key));

	os_memcpy(rnd, server_random, SSL3_RANDOM_SIZE);
	os_memcpy(rnd + SSL3_RANDOM_SIZE, client_random, SSL3_RANDOM_SIZE);

	if (os_strcmp(ver, "TLSv1.2") == 0) {
		tls_prf_sha256(master_key, master_key_len,
			       "key expansion", rnd, 2 * SSL3_RANDOM_SIZE,
			       _out, skip + out_len);
		ret = 0;
	} else if (tls_prf_sha1_md5(master_key, master_key_len,
				    "key expansion", rnd, 2 * SSL3_RANDOM_SIZE,
				    _out, skip + out_len) == 0) {
		ret = 0;
	}
	forced_memzero(master_key, sizeof(master_key));
	os_free(rnd);
	if (ret == 0)
		os_memcpy(out, _out + skip, out_len);
	bin_clear_free(tmp_out, skip);

	return ret;
#else /* OPENSSL_NEED_EAP_FAST_PRF */
	wpa_printf(MSG_ERROR,
		   "OpenSSL: EAP-FAST keys cannot be exported in FIPS mode");
	return -1;
#endif /* OPENSSL_NEED_EAP_FAST_PRF */
}