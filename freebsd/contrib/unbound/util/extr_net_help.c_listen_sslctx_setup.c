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
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_set_cipher_list (int /*<<< orphan*/ *,char*) ; 
 int SSL_CTX_set_options (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_security_level (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SSL_OP_CIPHER_SERVER_PREFERENCE ; 
 int SSL_OP_NO_SSLv2 ; 
 int SSL_OP_NO_SSLv3 ; 
 int SSL_OP_NO_TLSv1 ; 
 int SSL_OP_NO_TLSv1_1 ; 
 int /*<<< orphan*/  log_crypto_err (char*) ; 

int
listen_sslctx_setup(void* ctxt)
{
#ifdef HAVE_SSL
	SSL_CTX* ctx = (SSL_CTX*)ctxt;
	/* no SSLv2, SSLv3 because has defects */
	if((SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv2) & SSL_OP_NO_SSLv2)
		!= SSL_OP_NO_SSLv2){
		log_crypto_err("could not set SSL_OP_NO_SSLv2");
		return 0;
	}
	if((SSL_CTX_set_options(ctx, SSL_OP_NO_SSLv3) & SSL_OP_NO_SSLv3)
		!= SSL_OP_NO_SSLv3){
		log_crypto_err("could not set SSL_OP_NO_SSLv3");
		return 0;
	}
#if defined(SSL_OP_NO_TLSv1) && defined(SSL_OP_NO_TLSv1_1)
	/* if we have tls 1.1 disable 1.0 */
	if((SSL_CTX_set_options(ctx, SSL_OP_NO_TLSv1) & SSL_OP_NO_TLSv1)
		!= SSL_OP_NO_TLSv1){
		log_crypto_err("could not set SSL_OP_NO_TLSv1");
		return 0;
	}
#endif
#if defined(SSL_OP_NO_TLSv1_1) && defined(SSL_OP_NO_TLSv1_2)
	/* if we have tls 1.2 disable 1.1 */
	if((SSL_CTX_set_options(ctx, SSL_OP_NO_TLSv1_1) & SSL_OP_NO_TLSv1_1)
		!= SSL_OP_NO_TLSv1_1){
		log_crypto_err("could not set SSL_OP_NO_TLSv1_1");
		return 0;
	}
#endif
#if defined(SHA256_DIGEST_LENGTH) && defined(USE_ECDSA)
	/* if we have sha256, set the cipher list to have no known vulns */
	if(!SSL_CTX_set_cipher_list(ctx, "TLS13-CHACHA20-POLY1305-SHA256:TLS13-AES-256-GCM-SHA384:TLS13-AES-128-GCM-SHA256:ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256"))
		log_crypto_err("could not set cipher list with SSL_CTX_set_cipher_list");
#endif

	if((SSL_CTX_set_options(ctx, SSL_OP_CIPHER_SERVER_PREFERENCE) &
		SSL_OP_CIPHER_SERVER_PREFERENCE) !=
		SSL_OP_CIPHER_SERVER_PREFERENCE) {
		log_crypto_err("could not set SSL_OP_CIPHER_SERVER_PREFERENCE");
		return 0;
	}

#ifdef HAVE_SSL_CTX_SET_SECURITY_LEVEL
	SSL_CTX_set_security_level(ctx, 0);
#endif
#else
	(void)ctxt;
#endif /* HAVE_SSL */
	return 1;
}