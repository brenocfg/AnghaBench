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
 int /*<<< orphan*/  NID_sha1 ; 
 int RSA_sign (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,unsigned char*,unsigned int*,int /*<<< orphan*/ *) ; 
 unsigned char* SHA1 (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA_DIGEST_LENGTH ; 
 scalar_t__ ldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_buffer_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_buffer_position (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rdf_new_frm_data (int /*<<< orphan*/ ,unsigned int,scalar_t__) ; 

ldns_rdf *
ldns_sign_public_rsasha1(ldns_buffer *to_sign, RSA *key)
{
	unsigned char *sha1_hash;
	unsigned int siglen;
	ldns_rdf *sigdata_rdf;
	ldns_buffer *b64sig;
	int result;

	siglen = 0;
	b64sig = ldns_buffer_new(LDNS_MAX_PACKETLEN);
	if (!b64sig) {
		return NULL;
	}

	sha1_hash = SHA1((unsigned char*)ldns_buffer_begin(to_sign),
				  ldns_buffer_position(to_sign), NULL);
	if (!sha1_hash) {
		ldns_buffer_free(b64sig);
		return NULL;
	}

	result = RSA_sign(NID_sha1, sha1_hash, SHA_DIGEST_LENGTH,
				   (unsigned char*)ldns_buffer_begin(b64sig),
				   &siglen, key);
	if (result != 1) {
		ldns_buffer_free(b64sig);
		return NULL;
	}

	sigdata_rdf = ldns_rdf_new_frm_data(LDNS_RDF_TYPE_B64, siglen, 
								 ldns_buffer_begin(b64sig));
	ldns_buffer_free(b64sig); /* can't free this buffer ?? */
	return sigdata_rdf;
}