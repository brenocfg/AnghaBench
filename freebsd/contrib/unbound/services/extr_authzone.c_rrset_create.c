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
typedef  void* uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  void* time_t ;
struct packed_rrset_data {size_t* rr_len; int /*<<< orphan*/  count; int /*<<< orphan*/ ** rr_data; void** rr_ttl; int /*<<< orphan*/  trust; void* ttl; } ;
struct auth_rrset {scalar_t__ type; struct auth_rrset* next; struct packed_rrset_data* data; } ;
struct auth_data {struct auth_rrset* rrsets; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct auth_rrset*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  rrset_trust_prim_noglue ; 

__attribute__((used)) static struct auth_rrset*
rrset_create(struct auth_data* node, uint16_t rr_type, uint32_t rr_ttl,
	uint8_t* rdata, size_t rdatalen)
{
	struct auth_rrset* rrset = (struct auth_rrset*)calloc(1,
		sizeof(*rrset));
	struct auth_rrset* p, *prev;
	struct packed_rrset_data* d;
	if(!rrset) {
		log_err("out of memory");
		return NULL;
	}
	rrset->type = rr_type;

	/* the rrset data structure, with one RR */
	d = (struct packed_rrset_data*)calloc(1,
		sizeof(struct packed_rrset_data) + sizeof(size_t) +
		sizeof(uint8_t*) + sizeof(time_t) + rdatalen);
	if(!d) {
		free(rrset);
		log_err("out of memory");
		return NULL;
	}
	rrset->data = d;
	d->ttl = rr_ttl;
	d->trust = rrset_trust_prim_noglue;
	d->rr_len = (size_t*)((uint8_t*)d + sizeof(struct packed_rrset_data));
	d->rr_data = (uint8_t**)&(d->rr_len[1]);
	d->rr_ttl = (time_t*)&(d->rr_data[1]);
	d->rr_data[0] = (uint8_t*)&(d->rr_ttl[1]);

	/* insert the RR */
	d->rr_len[0] = rdatalen;
	d->rr_ttl[0] = rr_ttl;
	memmove(d->rr_data[0], rdata, rdatalen);
	d->count++;

	/* insert rrset into linked list for domain */
	/* find sorted place to link the rrset into the list */
	prev = NULL;
	p = node->rrsets;
	while(p && p->type<=rr_type) {
		prev = p;
		p = p->next;
	}
	/* so, prev is smaller, and p is larger than rr_type */
	rrset->next = p;
	if(prev) prev->next = rrset;
	else node->rrsets = rrset;
	return rrset;
}