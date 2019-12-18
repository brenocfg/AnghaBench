#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {size_t dname_len; int /*<<< orphan*/ * dname; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct module_env {int /*<<< orphan*/ * scratch_buffer; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  ds_get_digest_algo (struct ub_packed_rrset_key*,size_t) ; 
 int /*<<< orphan*/  query_dname_tolower (scalar_t__) ; 
 int /*<<< orphan*/  rrset_get_rdata (struct ub_packed_rrset_key*,size_t,int /*<<< orphan*/ **,size_t*) ; 
 int secalgo_ds_digest (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ,unsigned char*) ; 
 scalar_t__ sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int
ds_create_dnskey_digest(struct module_env* env, 
	struct ub_packed_rrset_key* dnskey_rrset, size_t dnskey_idx,
	struct ub_packed_rrset_key* ds_rrset, size_t ds_idx,
	uint8_t* digest)
{
	sldns_buffer* b = env->scratch_buffer;
	uint8_t* dnskey_rdata;
	size_t dnskey_len;
	rrset_get_rdata(dnskey_rrset, dnskey_idx, &dnskey_rdata, &dnskey_len);

	/* create digest source material in buffer 
	 * digest = digest_algorithm( DNSKEY owner name | DNSKEY RDATA);
	 *	DNSKEY RDATA = Flags | Protocol | Algorithm | Public Key. */
	sldns_buffer_clear(b);
	sldns_buffer_write(b, dnskey_rrset->rk.dname, 
		dnskey_rrset->rk.dname_len);
	query_dname_tolower(sldns_buffer_begin(b));
	sldns_buffer_write(b, dnskey_rdata+2, dnskey_len-2); /* skip rdatalen*/
	sldns_buffer_flip(b);
	
	return secalgo_ds_digest(ds_get_digest_algo(ds_rrset, ds_idx),
		(unsigned char*)sldns_buffer_begin(b), sldns_buffer_limit(b),
		(unsigned char*)digest);
}