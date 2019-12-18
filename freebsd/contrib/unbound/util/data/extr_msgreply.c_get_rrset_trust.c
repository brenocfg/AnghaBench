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
typedef  int uint16_t ;
struct rrset_parse {scalar_t__ section; scalar_t__ type; struct rrset_parse* rrset_all_next; } ;
struct msg_parse {int flags; struct rrset_parse* rrset_first; } ;
typedef  enum rrset_trust { ____Placeholder_rrset_trust } rrset_trust ;

/* Variables and functions */
 int BIT_AA ; 
 scalar_t__ LDNS_RR_TYPE_CNAME ; 
 scalar_t__ LDNS_RR_TYPE_DNAME ; 
 scalar_t__ LDNS_SECTION_ANSWER ; 
 scalar_t__ LDNS_SECTION_AUTHORITY ; 
 int rrset_trust_add_AA ; 
 int rrset_trust_add_noAA ; 
 int rrset_trust_ans_AA ; 
 int rrset_trust_ans_noAA ; 
 int rrset_trust_auth_AA ; 
 int rrset_trust_auth_noAA ; 
 int rrset_trust_none ; 

__attribute__((used)) static enum rrset_trust
get_rrset_trust(struct msg_parse* msg, struct rrset_parse* rrset)
{
	uint16_t AA = msg->flags & BIT_AA;
	if(rrset->section == LDNS_SECTION_ANSWER) {
		if(AA) {
			/* RFC2181 says remainder of CNAME chain is nonauth*/
			if(msg->rrset_first && 
				msg->rrset_first->section==LDNS_SECTION_ANSWER
				&& msg->rrset_first->type==LDNS_RR_TYPE_CNAME){
				if(rrset == msg->rrset_first)
					return rrset_trust_ans_AA;
				else 	return rrset_trust_ans_noAA;
			}
			if(msg->rrset_first && 
				msg->rrset_first->section==LDNS_SECTION_ANSWER
				&& msg->rrset_first->type==LDNS_RR_TYPE_DNAME){
				if(rrset == msg->rrset_first ||
				   rrset == msg->rrset_first->rrset_all_next)
					return rrset_trust_ans_AA;
				else 	return rrset_trust_ans_noAA;
			}
			return rrset_trust_ans_AA;
		}
		else	return rrset_trust_ans_noAA;
	} else if(rrset->section == LDNS_SECTION_AUTHORITY) {
		if(AA)	return rrset_trust_auth_AA;
		else	return rrset_trust_auth_noAA;
	} else {
		/* addit section */
		if(AA)	return rrset_trust_add_AA;
		else	return rrset_trust_add_noAA;
	}
	/* NOTREACHED */
	return rrset_trust_none;
}