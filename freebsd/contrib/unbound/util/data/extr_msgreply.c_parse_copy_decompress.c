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
struct rrset_parse {struct rrset_parse* rrset_all_next; } ;
struct reply_info {scalar_t__ ttl; size_t rrset_count; scalar_t__ serve_expired_ttl; int /*<<< orphan*/  prefetch_ttl; TYPE_2__** rrsets; int /*<<< orphan*/  security; } ;
struct regional {int dummy; } ;
struct packed_rrset_data {scalar_t__ ttl; } ;
struct msg_parse {struct rrset_parse* rrset_first; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;
struct TYPE_3__ {scalar_t__ data; } ;
struct TYPE_4__ {TYPE_1__ entry; } ;

/* Variables and functions */
 scalar_t__ MAX_TTL ; 
 scalar_t__ NORR_TTL ; 
 int /*<<< orphan*/  PREFETCH_TTL_CALC (scalar_t__) ; 
 scalar_t__ SERVE_EXPIRED_TTL ; 
 int /*<<< orphan*/  log_assert (struct reply_info*) ; 
 int /*<<< orphan*/  parse_copy_decompress_rrset (int /*<<< orphan*/ *,struct msg_parse*,struct rrset_parse*,struct regional*,TYPE_2__*) ; 
 int /*<<< orphan*/  sec_status_unchecked ; 

__attribute__((used)) static int
parse_copy_decompress(sldns_buffer* pkt, struct msg_parse* msg,
	struct reply_info* rep, struct regional* region)
{
	size_t i;
	struct rrset_parse *pset = msg->rrset_first;
	struct packed_rrset_data* data;
	log_assert(rep);
	rep->ttl = MAX_TTL;
	rep->security = sec_status_unchecked;
	if(rep->rrset_count == 0)
		rep->ttl = NORR_TTL;

	for(i=0; i<rep->rrset_count; i++) {
		if(!parse_copy_decompress_rrset(pkt, msg, pset, region,
			rep->rrsets[i]))
			return 0;
		data = (struct packed_rrset_data*)rep->rrsets[i]->entry.data;
		if(data->ttl < rep->ttl)
			rep->ttl = data->ttl;

		pset = pset->rrset_all_next;
	}
	rep->prefetch_ttl = PREFETCH_TTL_CALC(rep->ttl);
	rep->serve_expired_ttl = rep->ttl + SERVE_EXPIRED_TTL;
	return 1;
}