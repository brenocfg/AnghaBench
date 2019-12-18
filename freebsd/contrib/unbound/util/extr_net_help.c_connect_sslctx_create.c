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
typedef  void SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_check_private_key (void*) ; 
 int /*<<< orphan*/  SSL_CTX_free (void*) ; 
 int /*<<< orphan*/  SSL_CTX_load_verify_locations (void*,char*,int /*<<< orphan*/ *) ; 
 void* SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int SSL_CTX_set_options (void*,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_verify (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_use_PrivateKey_file (void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_use_certificate_chain_file (void*,char*) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int SSL_OP_NO_SSLv2 ; 
 int SSL_OP_NO_SSLv3 ; 
 int /*<<< orphan*/  SSL_VERIFY_PEER ; 
 int /*<<< orphan*/  SSLv23_client_method () ; 
 int /*<<< orphan*/  add_WIN_cacerts_to_openssl_store (void*) ; 
 int /*<<< orphan*/  log_crypto_err (char*) ; 
 int /*<<< orphan*/  log_err (char*,char*) ; 

void* connect_sslctx_create(char* key, char* pem, char* verifypem, int wincert)
{
#ifdef HAVE_SSL
	SSL_CTX* ctx = SSL_CTX_new(SSLv23_client_method());
	if(!ctx) {
		log_crypto_err("could not allocate SSL_CTX pointer");
		return NULL;
	}
	if((SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2) & SSL_OP_NO_SSLv2)
		!= SSL_OP_NO_SSLv2) {
		log_crypto_err("could not set SSL_OP_NO_SSLv2");
		SSL_CTX_free(ctx);
		return NULL;
	}
	if((SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv3) & SSL_OP_NO_SSLv3)
		!= SSL_OP_NO_SSLv3) {
		log_crypto_err("could not set SSL_OP_NO_SSLv3");
		SSL_CTX_free(ctx);
		return NULL;
	}
	if(key && key[0]) {
		if(!SSL_CTX_use_certificate_chain_file(ctx, pem)) {
			log_err("error in client certificate %s", pem);
			log_crypto_err("error in certificate file");
			SSL_CTX_free(ctx);
			return NULL;
		}
		if(!SSL_CTX_use_PrivateKey_file(ctx, key, SSL_FILETYPE_PEM)) {
			log_err("error in client private key %s", key);
			log_crypto_err("error in key file");
			SSL_CTX_free(ctx);
			return NULL;
		}
		if(!SSL_CTX_check_private_key(ctx)) {
			log_err("error in client key %s", key);
			log_crypto_err("error in SSL_CTX_check_private_key");
			SSL_CTX_free(ctx);
			return NULL;
		}
	}
	if((verifypem && verifypem[0]) || wincert) {
		if(verifypem && verifypem[0]) {
			if(!SSL_CTX_load_verify_locations(ctx, verifypem, NULL)) {
				log_crypto_err("error in SSL_CTX verify");
				SSL_CTX_free(ctx);
				return NULL;
			}
		}
#ifdef USE_WINSOCK
		if(wincert) {
			if(!add_WIN_cacerts_to_openssl_store(ctx)) {
				log_crypto_err("error in add_WIN_cacerts_to_openssl_store");
				SSL_CTX_free(ctx);
				return NULL;
			}
		}
#else
		(void)wincert;
#endif
		SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, NULL);
	}
	return ctx;
#else
	(void)key; (void)pem; (void)verifypem; (void)wincert;
	return NULL;
#endif
}