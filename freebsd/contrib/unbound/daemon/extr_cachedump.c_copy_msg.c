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
struct ub_packed_rrset_key {int dummy; } ;
struct rrset_ref {int dummy; } ;
struct reply_info {int rrset_count; int /*<<< orphan*/ * ref; struct ub_packed_rrset_key** rrsets; } ;
struct regional {int dummy; } ;
struct query_info {int qname_len; int /*<<< orphan*/ * qname; } ;
struct lruhash_entry {int /*<<< orphan*/ * key; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int RR_COUNT_MAX ; 
 int /*<<< orphan*/ * regional_alloc_init (struct regional*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
copy_msg(struct regional* region, struct lruhash_entry* e, 
	struct query_info** k, struct reply_info** d)
{
	struct reply_info* rep = (struct reply_info*)e->data;
	if(rep->rrset_count > RR_COUNT_MAX)
		return 0; /* to protect against integer overflow */
	*d = (struct reply_info*)regional_alloc_init(region, e->data,
		sizeof(struct reply_info) + 
		sizeof(struct rrset_ref) * (rep->rrset_count-1) +
		sizeof(struct ub_packed_rrset_key*) * rep->rrset_count);
	if(!*d)
		return 0;
	(*d)->rrsets = (struct ub_packed_rrset_key**)(void *)(
		(uint8_t*)(&((*d)->ref[0])) + 
		sizeof(struct rrset_ref) * rep->rrset_count);
	*k = (struct query_info*)regional_alloc_init(region, 
		e->key, sizeof(struct query_info));
	if(!*k)
		return 0;
	(*k)->qname = regional_alloc_init(region, 
		(*k)->qname, (*k)->qname_len);
	return (*k)->qname != NULL;
}