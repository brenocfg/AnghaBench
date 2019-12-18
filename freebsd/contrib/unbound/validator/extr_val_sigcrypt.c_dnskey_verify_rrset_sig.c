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
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  time_t ;
struct val_env {int dummy; } ;
struct TYPE_2__ {scalar_t__* dname; int /*<<< orphan*/  type; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct regional {int dummy; } ;
struct rbtree_type {int dummy; } ;
struct module_qstate {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_pkt_section ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  enum sec_status { ____Placeholder_sec_status } sec_status ;

/* Variables and functions */
 int DNSKEY_BIT_ZSK ; 
 scalar_t__ LDNS_DNSSEC_KEYPROTO ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  adjust_ttl (struct val_env*,int /*<<< orphan*/ ,struct ub_packed_rrset_key*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  check_dates (struct val_env*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,char**) ; 
 int dname_signame_label_count (scalar_t__*) ; 
 int /*<<< orphan*/  dname_subdomain_c (scalar_t__*,scalar_t__*) ; 
 size_t dname_valid (scalar_t__*,size_t) ; 
 int /*<<< orphan*/  dnskey_calc_keytag (struct ub_packed_rrset_key*,size_t) ; 
 int dnskey_get_algo (struct ub_packed_rrset_key*,size_t) ; 
 int dnskey_get_flags (struct ub_packed_rrset_key*,size_t) ; 
 scalar_t__ dnskey_get_protocol (struct ub_packed_rrset_key*,size_t) ; 
 int /*<<< orphan*/  dnskey_get_pubkey (struct ub_packed_rrset_key*,size_t,unsigned char**,unsigned int*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  log_nametypeclass (int /*<<< orphan*/ ,char*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ query_dname_compare (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  rrset_canonical (struct regional*,int /*<<< orphan*/ *,struct ub_packed_rrset_key*,scalar_t__*,int,struct rbtree_type**,int /*<<< orphan*/ ,struct module_qstate*) ; 
 size_t rrset_get_count (struct ub_packed_rrset_key*) ; 
 int /*<<< orphan*/  rrset_get_rdata (struct ub_packed_rrset_key*,size_t,scalar_t__**,size_t*) ; 
 int sec_status_bogus ; 
 int sec_status_secure ; 
 int sec_status_unchecked ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 
 int verify_canonrrset (int /*<<< orphan*/ *,int,unsigned char*,unsigned int,unsigned char*,unsigned int,char**) ; 

enum sec_status 
dnskey_verify_rrset_sig(struct regional* region, sldns_buffer* buf, 
	struct val_env* ve, time_t now,
        struct ub_packed_rrset_key* rrset, struct ub_packed_rrset_key* dnskey,
        size_t dnskey_idx, size_t sig_idx,
	struct rbtree_type** sortree, int* buf_canon, char** reason,
	sldns_pkt_section section, struct module_qstate* qstate)
{
	enum sec_status sec;
	uint8_t* sig;		/* RRSIG rdata */
	size_t siglen;
	size_t rrnum = rrset_get_count(rrset);
	uint8_t* signer;	/* rrsig signer name */
	size_t signer_len;
	unsigned char* sigblock; /* signature rdata field */
	unsigned int sigblock_len;
	uint16_t ktag;		/* DNSKEY key tag */
	unsigned char* key;	/* public key rdata field */
	unsigned int keylen;
	rrset_get_rdata(rrset, rrnum + sig_idx, &sig, &siglen);
	/* min length of rdatalen, fixed rrsig, root signer, 1 byte sig */
	if(siglen < 2+20) {
		verbose(VERB_QUERY, "verify: signature too short");
		*reason = "signature too short";
		return sec_status_bogus;
	}

	if(!(dnskey_get_flags(dnskey, dnskey_idx) & DNSKEY_BIT_ZSK)) {
		verbose(VERB_QUERY, "verify: dnskey without ZSK flag");
		*reason = "dnskey without ZSK flag";
		return sec_status_bogus; 
	}

	if(dnskey_get_protocol(dnskey, dnskey_idx) != LDNS_DNSSEC_KEYPROTO) { 
		/* RFC 4034 says DNSKEY PROTOCOL MUST be 3 */
		verbose(VERB_QUERY, "verify: dnskey has wrong key protocol");
		*reason = "dnskey has wrong protocolnumber";
		return sec_status_bogus;
	}

	/* verify as many fields in rrsig as possible */
	signer = sig+2+18;
	signer_len = dname_valid(signer, siglen-2-18);
	if(!signer_len) {
		verbose(VERB_QUERY, "verify: malformed signer name");
		*reason = "signer name malformed";
		return sec_status_bogus; /* signer name invalid */
	}
	if(!dname_subdomain_c(rrset->rk.dname, signer)) {
		verbose(VERB_QUERY, "verify: signer name is off-tree");
		*reason = "signer name off-tree";
		return sec_status_bogus; /* signer name offtree */
	}
	sigblock = (unsigned char*)signer+signer_len;
	if(siglen < 2+18+signer_len+1) {
		verbose(VERB_QUERY, "verify: too short, no signature data");
		*reason = "signature too short, no signature data";
		return sec_status_bogus; /* sig rdf is < 1 byte */
	}
	sigblock_len = (unsigned int)(siglen - 2 - 18 - signer_len);

	/* verify key dname == sig signer name */
	if(query_dname_compare(signer, dnskey->rk.dname) != 0) {
		verbose(VERB_QUERY, "verify: wrong key for rrsig");
		log_nametypeclass(VERB_QUERY, "RRSIG signername is", 
			signer, 0, 0);
		log_nametypeclass(VERB_QUERY, "the key name is", 
			dnskey->rk.dname, 0, 0);
		*reason = "signer name mismatches key name";
		return sec_status_bogus;
	}

	/* verify covered type */
	/* memcmp works because type is in network format for rrset */
	if(memcmp(sig+2, &rrset->rk.type, 2) != 0) {
		verbose(VERB_QUERY, "verify: wrong type covered");
		*reason = "signature covers wrong type";
		return sec_status_bogus;
	}
	/* verify keytag and sig algo (possibly again) */
	if((int)sig[2+2] != dnskey_get_algo(dnskey, dnskey_idx)) {
		verbose(VERB_QUERY, "verify: wrong algorithm");
		*reason = "signature has wrong algorithm";
		return sec_status_bogus;
	}
	ktag = htons(dnskey_calc_keytag(dnskey, dnskey_idx));
	if(memcmp(sig+2+16, &ktag, 2) != 0) {
		verbose(VERB_QUERY, "verify: wrong keytag");
		*reason = "signature has wrong keytag";
		return sec_status_bogus;
	}

	/* verify labels is in a valid range */
	if((int)sig[2+3] > dname_signame_label_count(rrset->rk.dname)) {
		verbose(VERB_QUERY, "verify: labelcount out of range");
		*reason = "signature labelcount out of range";
		return sec_status_bogus;
	}

	/* original ttl, always ok */

	if(!*buf_canon) {
		/* create rrset canonical format in buffer, ready for 
		 * signature */
		if(!rrset_canonical(region, buf, rrset, sig+2, 
			18 + signer_len, sortree, section, qstate)) {
			log_err("verify: failed due to alloc error");
			return sec_status_unchecked;
		}
		*buf_canon = 1;
	}

	/* check that dnskey is available */
	dnskey_get_pubkey(dnskey, dnskey_idx, &key, &keylen);
	if(!key) {
		verbose(VERB_QUERY, "verify: short DNSKEY RR");
		return sec_status_unchecked;
	}

	/* verify */
	sec = verify_canonrrset(buf, (int)sig[2+2],
		sigblock, sigblock_len, key, keylen, reason);
	
	if(sec == sec_status_secure) {
		/* check if TTL is too high - reduce if so */
		adjust_ttl(ve, now, rrset, sig+2+4, sig+2+8, sig+2+12);

		/* verify inception, expiration dates 
		 * Do this last so that if you ignore expired-sigs the
		 * rest is sure to be OK. */
		if(!check_dates(ve, now, sig+2+8, sig+2+12, reason)) {
			return sec_status_bogus;
		}
	}

	return sec;
}