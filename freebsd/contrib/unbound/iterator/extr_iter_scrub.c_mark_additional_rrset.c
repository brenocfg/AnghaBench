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
struct rrset_parse {scalar_t__ section; int /*<<< orphan*/  flags; int /*<<< orphan*/  rrset_class; struct rr_parse* rr_first; int /*<<< orphan*/  type; } ;
struct rr_parse {struct rr_parse* next; } ;
struct msg_parse {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
typedef  int /*<<< orphan*/  hashvalue_type ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_A ; 
 int /*<<< orphan*/  LDNS_RR_TYPE_AAAA ; 
 scalar_t__ LDNS_SECTION_ADDITIONAL ; 
 int /*<<< orphan*/  RRSET_SCRUB_OK ; 
 scalar_t__ get_additional_name (struct rrset_parse*,struct rr_parse*,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  has_additional (int /*<<< orphan*/ ) ; 
 struct rrset_parse* msgparse_hashtable_lookup (struct msg_parse*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_hash_rrset (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mark_additional_rrset(sldns_buffer* pkt, struct msg_parse* msg, 
	struct rrset_parse* rrset)
{
	/* Mark A and AAAA for NS as appropriate additional section info. */
	uint8_t* nm = NULL;
	size_t nmlen = 0;
	struct rr_parse* rr;

	if(!has_additional(rrset->type))
		return;
	for(rr = rrset->rr_first; rr; rr = rr->next) {
		if(get_additional_name(rrset, rr, &nm, &nmlen, pkt)) {
			/* mark A */
			hashvalue_type h = pkt_hash_rrset(pkt, nm,
				LDNS_RR_TYPE_A, rrset->rrset_class, 0);
			struct rrset_parse* r = msgparse_hashtable_lookup(
				msg, pkt, h, 0, nm, nmlen, 
				LDNS_RR_TYPE_A, rrset->rrset_class);
			if(r && r->section == LDNS_SECTION_ADDITIONAL) {
				r->flags |= RRSET_SCRUB_OK;
			}
			
			/* mark AAAA */
			h = pkt_hash_rrset(pkt, nm, LDNS_RR_TYPE_AAAA, 
				rrset->rrset_class, 0);
			r = msgparse_hashtable_lookup(msg, pkt, h, 0, nm, 
				nmlen, LDNS_RR_TYPE_AAAA, rrset->rrset_class);
			if(r && r->section == LDNS_SECTION_ADDITIONAL) {
				r->flags |= RRSET_SCRUB_OK;
			}
		}
	}
}