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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct rrset_parse {int rr_count; int size; TYPE_1__* rr_first; TYPE_1__* rr_last; struct rr_parse* rrsig_first; } ;
struct rr_parse {scalar_t__ size; struct rr_parse* next; } ;
struct TYPE_2__ {int size; int /*<<< orphan*/ * ttl_data; int /*<<< orphan*/ * next; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static int
parse_get_cname_target(struct rrset_parse* rrset, uint8_t** sname, 
	size_t* snamelen)
{
	if(rrset->rr_count != 1) {
		struct rr_parse* sig;
		verbose(VERB_ALGO, "Found CNAME rrset with "
			"size > 1: %u", (unsigned)rrset->rr_count);
		/* use the first CNAME! */
		rrset->rr_count = 1;
		rrset->size = rrset->rr_first->size;
		for(sig=rrset->rrsig_first; sig; sig=sig->next)
			rrset->size += sig->size;
		rrset->rr_last = rrset->rr_first;
		rrset->rr_first->next = NULL;
	}
	if(rrset->rr_first->size < sizeof(uint16_t)+1)
		return 0; /* CNAME rdata too small */
	*sname = rrset->rr_first->ttl_data + sizeof(uint32_t)
		+ sizeof(uint16_t); /* skip ttl, rdatalen */
	*snamelen = rrset->rr_first->size - sizeof(uint16_t);
	return 1;
}