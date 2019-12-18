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
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct ub_packed_rrset_key {TYPE_1__ rk; } ;
struct regional {int dummy; } ;
struct delegpt {int dummy; } ;

/* Variables and functions */
 scalar_t__ LDNS_RR_TYPE_A ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 scalar_t__ LDNS_RR_TYPE_NS ; 
 int delegpt_add_rrset_A (struct delegpt*,struct regional*,struct ub_packed_rrset_key*,int /*<<< orphan*/ ) ; 
 int delegpt_add_rrset_AAAA (struct delegpt*,struct regional*,struct ub_packed_rrset_key*,int /*<<< orphan*/ ) ; 
 int delegpt_rrset_add_ns (struct delegpt*,struct regional*,struct ub_packed_rrset_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warn (char*) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 

int 
delegpt_add_rrset(struct delegpt* dp, struct regional* region,
        struct ub_packed_rrset_key* rrset, uint8_t lame)
{
	if(!rrset)
		return 1;
	if(ntohs(rrset->rk.type) == LDNS_RR_TYPE_NS)
		return delegpt_rrset_add_ns(dp, region, rrset, lame);
	else if(ntohs(rrset->rk.type) == LDNS_RR_TYPE_A)
		return delegpt_add_rrset_A(dp, region, rrset, lame);
	else if(ntohs(rrset->rk.type) == LDNS_RR_TYPE_AAAA)
		return delegpt_add_rrset_AAAA(dp, region, rrset, lame);
	log_warn("Unknown rrset type added to delegpt");
	return 1;
}