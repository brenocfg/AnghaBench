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
typedef  int /*<<< orphan*/  ldns_rdf ;
typedef  int /*<<< orphan*/  ldns_key ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RDF_TYPE_B64 ; 
 int /*<<< orphan*/  ldns_buffer_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ldns_key_hmac_key (int /*<<< orphan*/  const*) ; 
 size_t ldns_key_hmac_size (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ldns_rdf2buffer_str (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_rdf_deep_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_rdf_new_frm_data (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ldns_status
ldns_hmac_key2buffer_str(ldns_buffer *output, const ldns_key *k)
{
	ldns_status status;
	size_t i;
	ldns_rdf *b64_bignum;

	ldns_buffer_printf(output, "Key: ");

 	i = ldns_key_hmac_size(k);
	b64_bignum =  ldns_rdf_new_frm_data(LDNS_RDF_TYPE_B64, i, ldns_key_hmac_key(k));
	status = ldns_rdf2buffer_str(output, b64_bignum);
	ldns_rdf_deep_free(b64_bignum);
	ldns_buffer_printf(output, "\n");
	return status;
}