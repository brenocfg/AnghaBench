#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ldns_status ;
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_buffer ;
struct TYPE_6__ {int /*<<< orphan*/ * s; int /*<<< orphan*/ * r; } ;
typedef  TYPE_1__ DSA_SIG ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_bin2bn (unsigned char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  DSA_SIG_free (TYPE_1__*) ; 
 TYPE_1__* DSA_SIG_new () ; 
 int /*<<< orphan*/  DSA_SIG_set0 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LDNS_STATUS_CRYPTO_ALGO_NOT_IMPL ; 
 int /*<<< orphan*/  LDNS_STATUS_MEM_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_SSL_ERR ; 
 int /*<<< orphan*/  LDNS_STATUS_SYNTAX_RDATA_ERR ; 
 int SHA_DIGEST_LENGTH ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int i2d_DSA_SIG (TYPE_1__*,unsigned char**) ; 
 scalar_t__ ldns_buffer_reserve (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ldns_buffer_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_write (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 scalar_t__ ldns_rdf_data (int /*<<< orphan*/  const*) ; 
 int ldns_rdf_size (int /*<<< orphan*/  const*) ; 

ldns_status
ldns_convert_dsa_rrsig_rdf2asn1(ldns_buffer *target_buffer,
						  const ldns_rdf *sig_rdf)
{
#ifdef USE_DSA
	/* the EVP api wants the DER encoding of the signature... */
	BIGNUM *R, *S;
	DSA_SIG *dsasig;
	unsigned char *raw_sig = NULL;
	int raw_sig_len;

        if(ldns_rdf_size(sig_rdf) < 1 + 2*SHA_DIGEST_LENGTH)
                return LDNS_STATUS_SYNTAX_RDATA_ERR;
	/* extract the R and S field from the sig buffer */
	R = BN_new();
	if(!R) return LDNS_STATUS_MEM_ERR;
	(void) BN_bin2bn((unsigned char *) ldns_rdf_data(sig_rdf) + 1,
	                 SHA_DIGEST_LENGTH, R);
	S = BN_new();
	if(!S) {
		BN_free(R);
		return LDNS_STATUS_MEM_ERR;
	}
	(void) BN_bin2bn((unsigned char *) ldns_rdf_data(sig_rdf) + 21,
	                 SHA_DIGEST_LENGTH, S);

	dsasig = DSA_SIG_new();
	if (!dsasig) {
		BN_free(R);
		BN_free(S);
		return LDNS_STATUS_MEM_ERR;
	}
# ifdef HAVE_DSA_SIG_SET0
       if (! DSA_SIG_set0(dsasig, R, S))
	       return LDNS_STATUS_SSL_ERR;
# else
	dsasig->r = R;
	dsasig->s = S;
# endif

	raw_sig_len = i2d_DSA_SIG(dsasig, &raw_sig);
	if (raw_sig_len < 0) {
		DSA_SIG_free(dsasig);
		free(raw_sig);
		return LDNS_STATUS_SSL_ERR;
	}
	if (ldns_buffer_reserve(target_buffer, (size_t) raw_sig_len)) {
		ldns_buffer_write(target_buffer, raw_sig, (size_t)raw_sig_len);
	}

	DSA_SIG_free(dsasig);
	free(raw_sig);

	return ldns_buffer_status(target_buffer);
#else
	(void)target_buffer; (void)sig_rdf;
	return LDNS_STATUS_CRYPTO_ALGO_NOT_IMPL;
#endif
}