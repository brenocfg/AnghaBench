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
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_buffer ;
typedef  int /*<<< orphan*/  RSA ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_PACKETLEN ; 
 int /*<<< orphan*/  LDNS_RDF_TYPE_B64 ; 
 unsigned char* MD5 (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5_DIGEST_LENGTH ; 
 int /*<<< orphan*/  NID_md5 ; 
 int /*<<< orphan*/  RSA_sign (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,unsigned char*,unsigned int*,int /*<<< orphan*/ *) ; 
 scalar_t__ ldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_buffer_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_buffer_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rdf_new_frm_data (int /*<<< orphan*/ ,unsigned int,scalar_t__) ; 

ldns_rdf *
ldns_sign_public_rsamd5(ldns_buffer *to_sign, RSA *key)
{
	unsigned char *md5_hash;
	unsigned int siglen;
	ldns_rdf *sigdata_rdf;
	ldns_buffer *b64sig;

	b64sig = ldns_buffer_new(LDNS_MAX_PACKETLEN);
	if (!b64sig) {
		return NULL;
	}

	md5_hash = MD5((unsigned char*)ldns_buffer_begin(to_sign),
				ldns_buffer_position(to_sign), NULL);
	if (!md5_hash) {
		ldns_buffer_free(b64sig);
		return NULL;
	}

	RSA_sign(NID_md5, md5_hash, MD5_DIGEST_LENGTH,
		    (unsigned char*)ldns_buffer_begin(b64sig),
		    &siglen, key);

	sigdata_rdf = ldns_rdf_new_frm_data(LDNS_RDF_TYPE_B64, siglen,
								 ldns_buffer_begin(b64sig));
	ldns_buffer_free(b64sig);
	return sigdata_rdf;
}