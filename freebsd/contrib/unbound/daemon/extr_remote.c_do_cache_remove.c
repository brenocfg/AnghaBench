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
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  msg_cache; int /*<<< orphan*/  rrset_cache; } ;
struct worker {TYPE_1__ env; } ;
struct query_info {size_t qname_len; int /*<<< orphan*/ * local_alias; scalar_t__ qclass; scalar_t__ qtype; int /*<<< orphan*/ * qname; } ;
typedef  int /*<<< orphan*/  hashvalue_type ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_CD ; 
 scalar_t__ LDNS_RR_TYPE_AAAA ; 
 scalar_t__ LDNS_RR_TYPE_SOA ; 
 int /*<<< orphan*/  PACKED_RRSET_SOA_NEG ; 
 int /*<<< orphan*/  query_info_hash (struct query_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrset_cache_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slabhash_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct query_info*) ; 

__attribute__((used)) static void
do_cache_remove(struct worker* worker, uint8_t* nm, size_t nmlen,
	uint16_t t, uint16_t c)
{
	hashvalue_type h;
	struct query_info k;
	rrset_cache_remove(worker->env.rrset_cache, nm, nmlen, t, c, 0);
	if(t == LDNS_RR_TYPE_SOA)
		rrset_cache_remove(worker->env.rrset_cache, nm, nmlen, t, c,
			PACKED_RRSET_SOA_NEG);
	k.qname = nm;
	k.qname_len = nmlen;
	k.qtype = t;
	k.qclass = c;
	k.local_alias = NULL;
	h = query_info_hash(&k, 0);
	slabhash_remove(worker->env.msg_cache, h, &k);
	if(t == LDNS_RR_TYPE_AAAA) {
		/* for AAAA also flush dns64 bit_cd packet */
		h = query_info_hash(&k, BIT_CD);
		slabhash_remove(worker->env.msg_cache, h, &k);
	}
}