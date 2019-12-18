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
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new_by_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NID_X9_62_prime256v1 ; 
 int /*<<< orphan*/  SSL_CTX_set_ecdh_auto (int /*<<< orphan*/ *,int) ; 
 int SSL_CTX_set_tmp_ecdh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_crypto_err (char*) ; 

void
listen_sslctx_setup_2(void* ctxt)
{
#ifdef HAVE_SSL
	SSL_CTX* ctx = (SSL_CTX*)ctxt;
	(void)ctx;
#if HAVE_DECL_SSL_CTX_SET_ECDH_AUTO
	if(!SSL_CTX_set_ecdh_auto(ctx,1)) {
		log_crypto_err("Error in SSL_CTX_ecdh_auto, not enabling ECDHE");
	}
#elif defined(USE_ECDSA)
	if(1) {
		EC_KEY *ecdh = EC_KEY_new_by_curve_name (NID_X9_62_prime256v1);
		if (!ecdh) {
			log_crypto_err("could not find p256, not enabling ECDHE");
		} else {
			if (1 != SSL_CTX_set_tmp_ecdh (ctx, ecdh)) {
				log_crypto_err("Error in SSL_CTX_set_tmp_ecdh, not enabling ECDHE");
			}
			EC_KEY_free (ecdh);
		}
	}
#endif
#else
	(void)ctxt;
#endif /* HAVE_SSL */
}