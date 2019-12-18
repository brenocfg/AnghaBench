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
struct rrset_parse {int section; struct rrset_parse* rrset_all_next; } ;
struct msg_parse {int /*<<< orphan*/  ar_rrsets; int /*<<< orphan*/  ns_rrsets; struct rrset_parse* rrset_last; struct rrset_parse* rrset_first; int /*<<< orphan*/  an_rrsets; } ;
typedef  int sldns_pkt_section ;

/* Variables and functions */
#define  LDNS_SECTION_ADDITIONAL 130 
#define  LDNS_SECTION_ANSWER 129 
#define  LDNS_SECTION_AUTHORITY 128 
 int /*<<< orphan*/  log_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
change_section(struct msg_parse* msg, struct rrset_parse* rrset,
	sldns_pkt_section section)
{
	struct rrset_parse *p, *prev;
	/* remove from list */
	if(section == rrset->section)
		return;
	p = msg->rrset_first;
	prev = 0;
	while(p) {
		if(p == rrset) {
			if(prev) prev->rrset_all_next = p->rrset_all_next;
			else	msg->rrset_first = p->rrset_all_next;
			if(msg->rrset_last == rrset)
				msg->rrset_last = prev;
			break;
		}
		prev = p;
		p = p->rrset_all_next;
	}
	/* remove from count */
	switch(rrset->section) {
		case LDNS_SECTION_ANSWER: msg->an_rrsets--; break;
		case LDNS_SECTION_AUTHORITY: msg->ns_rrsets--; break;
		case LDNS_SECTION_ADDITIONAL: msg->ar_rrsets--; break;
		default: log_assert(0);
	}
	/* insert at end of list */
	rrset->rrset_all_next = 0;
	if(msg->rrset_last)
		msg->rrset_last->rrset_all_next = rrset;
	else	msg->rrset_first = rrset;
	msg->rrset_last = rrset;
	/* up count of new section */
	switch(section) {
		case LDNS_SECTION_AUTHORITY: msg->ns_rrsets++; break;
		case LDNS_SECTION_ADDITIONAL: msg->ar_rrsets++; break;
		default: log_assert(0);
	}
	rrset->section = section;
}