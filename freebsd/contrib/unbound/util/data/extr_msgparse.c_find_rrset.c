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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct rrset_parse {int /*<<< orphan*/ * dname; } ;
struct regional {int dummy; } ;
struct msg_parse {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_pkt_section ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  hashvalue_type ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_NSEC ; 
 scalar_t__ LDNS_RR_TYPE_RRSIG ; 
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 int /*<<< orphan*/  PACKED_RRSET_NSEC_AT_APEX ; 
 int /*<<< orphan*/  PACKED_RRSET_SOA_NEG ; 
 struct rrset_parse* change_rrsig_rrset (struct rrset_parse*,struct msg_parse*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct regional*) ; 
 struct rrset_parse* msgparse_hashtable_lookup (struct msg_parse*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pkt_hash_rrset_first (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pkt_hash_rrset_rest (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_rrset_flags (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pkt_rrsig_covered (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ pkt_rrsig_covered_equals (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ rrset_has_sigover (int /*<<< orphan*/ *,struct rrset_parse*,scalar_t__,int*) ; 
 int /*<<< orphan*/  sldns_buffer_current (int /*<<< orphan*/ *) ; 
 scalar_t__ smart_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
find_rrset(struct msg_parse* msg, sldns_buffer* pkt, uint8_t* dname, 
	size_t dnamelen, uint16_t type, uint16_t dclass, hashvalue_type* hash, 
	uint32_t* rrset_flags,
	uint8_t** prev_dname_first, uint8_t** prev_dname_last,
	size_t* prev_dnamelen, uint16_t* prev_type,
	uint16_t* prev_dclass, struct rrset_parse** rrset_prev,
	sldns_pkt_section section, struct regional* region)
{
	hashvalue_type dname_h = pkt_hash_rrset_first(pkt, dname);
	uint16_t covtype;
	if(*rrset_prev) {
		/* check if equal to previous item */
		if(type == *prev_type && dclass == *prev_dclass &&
			dnamelen == *prev_dnamelen &&
			smart_compare(pkt, dname, *prev_dname_first, 
				*prev_dname_last) == 0 &&
			type != LDNS_RR_TYPE_RRSIG) {
			/* same as previous */
			*prev_dname_last = dname;
			return 1;
		}
		/* check if rrsig over previous item */
		if(type == LDNS_RR_TYPE_RRSIG && dclass == *prev_dclass &&
			pkt_rrsig_covered_equals(pkt, sldns_buffer_current(pkt),
				*prev_type) &&
			smart_compare(pkt, dname, *prev_dname_first,
				*prev_dname_last) == 0) {
			/* covers previous */
			*prev_dname_last = dname;
			return 1;
		}
	}
	/* find by hashing and lookup in hashtable */
	*rrset_flags = pkt_rrset_flags(pkt, type, section);
	
	/* if rrsig - try to lookup matching data set first */
	if(type == LDNS_RR_TYPE_RRSIG && pkt_rrsig_covered(pkt, 
		sldns_buffer_current(pkt), &covtype)) {
		*hash = pkt_hash_rrset_rest(dname_h, covtype, dclass, 
			*rrset_flags);
		*rrset_prev = msgparse_hashtable_lookup(msg, pkt, *hash, 
			*rrset_flags, dname, dnamelen, covtype, dclass);
		if(!*rrset_prev && covtype == LDNS_RR_TYPE_NSEC) {
			/* if NSEC try with NSEC apex bit twiddled */
			*rrset_flags ^= PACKED_RRSET_NSEC_AT_APEX;
			*hash = pkt_hash_rrset_rest(dname_h, covtype, dclass, 
				*rrset_flags);
			*rrset_prev = msgparse_hashtable_lookup(msg, pkt, 
				*hash, *rrset_flags, dname, dnamelen, covtype, 
				dclass);
			if(!*rrset_prev) /* untwiddle if not found */
				*rrset_flags ^= PACKED_RRSET_NSEC_AT_APEX;
		}
		if(!*rrset_prev && covtype == LDNS_RR_TYPE_SOA) {
			/* if SOA try with SOA neg flag twiddled */
			*rrset_flags ^= PACKED_RRSET_SOA_NEG;
			*hash = pkt_hash_rrset_rest(dname_h, covtype, dclass, 
				*rrset_flags);
			*rrset_prev = msgparse_hashtable_lookup(msg, pkt, 
				*hash, *rrset_flags, dname, dnamelen, covtype, 
				dclass);
			if(!*rrset_prev) /* untwiddle if not found */
				*rrset_flags ^= PACKED_RRSET_SOA_NEG;
		}
		if(*rrset_prev) {
			*prev_dname_first = (*rrset_prev)->dname;
			*prev_dname_last = dname;
			*prev_dnamelen = dnamelen;
			*prev_type = covtype;
			*prev_dclass = dclass;
			return 1;
		}
	}
	if(type != LDNS_RR_TYPE_RRSIG) {
		int hasother = 0;
		/* find matching rrsig */
		*hash = pkt_hash_rrset_rest(dname_h, LDNS_RR_TYPE_RRSIG, 
			dclass, 0);
		*rrset_prev = msgparse_hashtable_lookup(msg, pkt, *hash, 
			0, dname, dnamelen, LDNS_RR_TYPE_RRSIG, 
			dclass);
		if(*rrset_prev && rrset_has_sigover(pkt, *rrset_prev, type,
			&hasother)) {
			/* yes! */
			*prev_dname_first = (*rrset_prev)->dname;
			*prev_dname_last = dname;
			*prev_dnamelen = dnamelen;
			*prev_type = type;
			*prev_dclass = dclass;
			*rrset_prev = change_rrsig_rrset(*rrset_prev, msg, 
				pkt, type, *rrset_flags, hasother, section, 
				region);
			if(!*rrset_prev) return 0;
			return 1;
		}
	}

	*hash = pkt_hash_rrset_rest(dname_h, type, dclass, *rrset_flags);
	*rrset_prev = msgparse_hashtable_lookup(msg, pkt, *hash, *rrset_flags, 
		dname, dnamelen, type, dclass);
	if(*rrset_prev)
		*prev_dname_first = (*rrset_prev)->dname;
	else 	*prev_dname_first = dname;
	*prev_dname_last = dname;
	*prev_dnamelen = dnamelen;
	*prev_type = type;
	*prev_dclass = dclass;
	return 1;
}