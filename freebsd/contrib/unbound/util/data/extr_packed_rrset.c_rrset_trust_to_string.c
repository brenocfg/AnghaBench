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
typedef  enum rrset_trust { ____Placeholder_rrset_trust } rrset_trust ;

/* Variables and functions */
#define  rrset_trust_add_AA 140 
#define  rrset_trust_add_noAA 139 
#define  rrset_trust_ans_AA 138 
#define  rrset_trust_ans_noAA 137 
#define  rrset_trust_auth_AA 136 
#define  rrset_trust_auth_noAA 135 
#define  rrset_trust_glue 134 
#define  rrset_trust_nonauth_ans_AA 133 
#define  rrset_trust_none 132 
#define  rrset_trust_prim_noglue 131 
#define  rrset_trust_sec_noglue 130 
#define  rrset_trust_ultimate 129 
#define  rrset_trust_validated 128 

const char* 
rrset_trust_to_string(enum rrset_trust s)
{
	switch(s) {
	case rrset_trust_none: 		return "rrset_trust_none";
	case rrset_trust_add_noAA: 	return "rrset_trust_add_noAA";
	case rrset_trust_auth_noAA: 	return "rrset_trust_auth_noAA";
	case rrset_trust_add_AA: 	return "rrset_trust_add_AA";
	case rrset_trust_nonauth_ans_AA:return "rrset_trust_nonauth_ans_AA";
	case rrset_trust_ans_noAA: 	return "rrset_trust_ans_noAA";
	case rrset_trust_glue: 		return "rrset_trust_glue";
	case rrset_trust_auth_AA: 	return "rrset_trust_auth_AA";
	case rrset_trust_ans_AA: 	return "rrset_trust_ans_AA";
	case rrset_trust_sec_noglue: 	return "rrset_trust_sec_noglue";
	case rrset_trust_prim_noglue: 	return "rrset_trust_prim_noglue";
	case rrset_trust_validated: 	return "rrset_trust_validated";
	case rrset_trust_ultimate: 	return "rrset_trust_ultimate";
	}
	return "unknown_rrset_trust_value";
}