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
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_buffer ;
typedef  int /*<<< orphan*/  EVP_PKEY ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_MD_CTX_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_new () ; 
 int EVP_VerifyFinal (int /*<<< orphan*/ *,unsigned char const*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EVP_VerifyInit (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EVP_VerifyUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDNS_STATUS_CRYPTO_BOGUS ; 
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_OK ; 
 int /*<<< orphan*/  LDNS_STATUS_SSL_ERR ; 
 int /*<<< orphan*/  ldns_buffer_begin (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_buffer_position (int /*<<< orphan*/  const*) ; 
 scalar_t__ malloc (int) ; 

ldns_status
ldns_verify_rrsig_evp_raw(const unsigned char *sig, size_t siglen, 
					 const ldns_buffer *rrset, EVP_PKEY *key, const EVP_MD *digest_type)
{
	EVP_MD_CTX *ctx;
	int res;

#ifdef HAVE_EVP_MD_CTX_NEW
	ctx = EVP_MD_CTX_new();
#else
	ctx = (EVP_MD_CTX*)malloc(sizeof(*ctx));
	if(ctx) EVP_MD_CTX_init(ctx);
#endif
	if(!ctx)
		return LDNS_STATUS_MEM_ERR;
	
	EVP_VerifyInit(ctx, digest_type);
	EVP_VerifyUpdate(ctx,
				  ldns_buffer_begin(rrset),
				  ldns_buffer_position(rrset));
	res = EVP_VerifyFinal(ctx, sig, (unsigned int) siglen, key);
	
	EVP_MD_CTX_destroy(ctx);
	
	if (res == 1) {
		return LDNS_STATUS_OK;
	} else if (res == 0) {
		return LDNS_STATUS_CRYPTO_BOGUS;
	}
	/* TODO how to communicate internal SSL error?
	   let caller use ssl's get_error() */
	return LDNS_STATUS_SSL_ERR;
}