#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ uint16_t ;
struct rrset_parse {scalar_t__ type; int /*<<< orphan*/ * dname; } ;
struct regional {int dummy; } ;
struct msg_parse {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_pkt_section ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  hashvalue_type ;
typedef  int /*<<< orphan*/  dclass ;
struct TYPE_4__ {char* name; } ;
struct TYPE_3__ {char* _name; } ;

/* Variables and functions */
 int LDNS_RCODE_FORMERR ; 
 int LDNS_RCODE_SERVFAIL ; 
 scalar_t__ LDNS_RR_TYPE_RRSIG ; 
 int add_rr_to_rrset (struct rrset_parse*,int /*<<< orphan*/ *,struct msg_parse*,struct regional*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dname_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_rrset (struct msg_parse*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ **,size_t*,scalar_t__*,scalar_t__*,struct rrset_parse**,int /*<<< orphan*/ ,struct regional*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct rrset_parse* new_rrset (struct msg_parse*,int /*<<< orphan*/ *,size_t,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct regional*) ; 
 scalar_t__ ntohs (scalar_t__) ; 
 size_t pkt_dname_len (int /*<<< orphan*/ *) ; 
 scalar_t__ pkt_rrsig_covered (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/ * sldns_buffer_current (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_read (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 scalar_t__ sldns_buffer_read_u16 (int /*<<< orphan*/ *) ; 
 int sldns_buffer_remaining (int /*<<< orphan*/ *) ; 
 TYPE_2__* sldns_lookup_by_id (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sldns_rr_classes ; 
 TYPE_1__* sldns_rr_descript (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int
parse_section(sldns_buffer* pkt, struct msg_parse* msg, 
	struct regional* region, sldns_pkt_section section, 
	uint16_t num_rrs, size_t* num_rrsets)
{
	uint16_t i;
	uint8_t* dname, *prev_dname_f = NULL, *prev_dname_l = NULL;
	size_t dnamelen, prev_dnamelen = 0;
	uint16_t type, prev_type = 0;
	uint16_t dclass, prev_dclass = 0;
	uint32_t rrset_flags = 0;
	hashvalue_type hash = 0;
	struct rrset_parse* rrset = NULL;
	int r;

	if(num_rrs == 0)
		return 0;
	if(sldns_buffer_remaining(pkt) <= 0)
		return LDNS_RCODE_FORMERR;
	for(i=0; i<num_rrs; i++) {
		/* parse this RR. */
		dname = sldns_buffer_current(pkt);
		if((dnamelen = pkt_dname_len(pkt)) == 0)
			return LDNS_RCODE_FORMERR;
		if(sldns_buffer_remaining(pkt) < 10) /* type, class, ttl, len */
			return LDNS_RCODE_FORMERR;
		type = sldns_buffer_read_u16(pkt);
		sldns_buffer_read(pkt, &dclass, sizeof(dclass));

		if(0) { /* debug show what is being parsed. */
			if(type == LDNS_RR_TYPE_RRSIG) {
				uint16_t t;
				if(pkt_rrsig_covered(pkt, 
					sldns_buffer_current(pkt), &t))
					fprintf(stderr, "parse of %s(%d) [%s(%d)]",
					sldns_rr_descript(type)?
					sldns_rr_descript(type)->_name: "??",
					(int)type,
					sldns_rr_descript(t)?
					sldns_rr_descript(t)->_name: "??",
					(int)t);
			} else
			  fprintf(stderr, "parse of %s(%d)",
				sldns_rr_descript(type)?
				sldns_rr_descript(type)->_name: "??",
				(int)type);
			fprintf(stderr, " %s(%d) ",
				sldns_lookup_by_id(sldns_rr_classes, 
				(int)ntohs(dclass))?sldns_lookup_by_id(
				sldns_rr_classes, (int)ntohs(dclass))->name: 
				"??", (int)ntohs(dclass));
			dname_print(stderr, pkt, dname);
			fprintf(stderr, "\n");
		}

		/* see if it is part of an existing RR set */
		if(!find_rrset(msg, pkt, dname, dnamelen, type, dclass, &hash, 
			&rrset_flags, &prev_dname_f, &prev_dname_l, 
			&prev_dnamelen, &prev_type, &prev_dclass, &rrset, 
			section, region))
			return LDNS_RCODE_SERVFAIL;
		if(!rrset) {
			/* it is a new RR set. hash&flags already calculated.*/
			(*num_rrsets)++;
			rrset = new_rrset(msg, dname, dnamelen, type, dclass,
				hash, rrset_flags, section, region);
			if(!rrset) 
				return LDNS_RCODE_SERVFAIL;
		}
		else if(0)	{ 
			fprintf(stderr, "is part of existing: ");
			dname_print(stderr, pkt, rrset->dname);
			fprintf(stderr, " type %s(%d)\n",
				sldns_rr_descript(rrset->type)?
				sldns_rr_descript(rrset->type)->_name: "??",
				(int)rrset->type);
		}
		/* add to rrset. */
		if((r=add_rr_to_rrset(rrset, pkt, msg, region, section, 
			type)) != 0)
			return r;
	}
	return 0;
}