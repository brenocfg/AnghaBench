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
struct sockaddr_storage {int dummy; } ;
struct rrset_parse {scalar_t__ dname_len; scalar_t__ rr_count; int /*<<< orphan*/  size; struct rr_parse* rr_last; int /*<<< orphan*/  rr_first; int /*<<< orphan*/  dname; } ;
struct rr_parse {scalar_t__ size; int /*<<< orphan*/  next; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ LDNS_MAX_DOMAINLEN ; 
 scalar_t__ VERB_QUERY ; 
 int /*<<< orphan*/  dname_pkt_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_name_addr (scalar_t__,char const*,int /*<<< orphan*/ *,struct sockaddr_storage*,int /*<<< orphan*/ ) ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static int
remove_rr(const char* str, sldns_buffer* pkt, struct rrset_parse* rrset,
	struct rr_parse* prev, struct rr_parse** rr, struct sockaddr_storage* addr, socklen_t addrlen)
{
	if(verbosity >= VERB_QUERY && rrset->dname_len <= LDNS_MAX_DOMAINLEN && str) {
		uint8_t buf[LDNS_MAX_DOMAINLEN+1];
		dname_pkt_copy(pkt, buf, rrset->dname);
		log_name_addr(VERB_QUERY, str, buf, addr, addrlen);
	}
	if(prev)
		prev->next = (*rr)->next;
	else	rrset->rr_first = (*rr)->next;
	if(rrset->rr_last == *rr)
		rrset->rr_last = prev;
	rrset->rr_count --;
	rrset->size -= (*rr)->size;
	/* rr struct still exists, but is unlinked, so that in the for loop
	 * the rr->next works fine to continue. */
	return rrset->rr_count == 0;
}