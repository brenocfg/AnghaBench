#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ time_t ;
struct TYPE_6__ {struct packed_rrset_data* data; int /*<<< orphan*/  hash; struct ub_packed_rrset_key* key; } ;
struct TYPE_5__ {int* dname; int /*<<< orphan*/  type; int /*<<< orphan*/  dname_len; } ;
struct ub_packed_rrset_key {TYPE_3__ entry; TYPE_2__ rk; } ;
struct TYPE_4__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {TYPE_1__ sin6_addr; } ;
struct regional {int dummy; } ;
struct packed_rrset_data {int count; size_t* rr_len; int** rr_data; scalar_t__* rr_ttl; int /*<<< orphan*/  security; int /*<<< orphan*/  trust; scalar_t__ rrsig_count; int /*<<< orphan*/  ttl; } ;
struct dns64_env {int /*<<< orphan*/  prefix_net; int /*<<< orphan*/  prefix_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_AAAA ; 
 int RR_COUNT_MAX ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 struct packed_rrset_data* regional_alloc (struct regional*,int) ; 
 scalar_t__ regional_alloc_init (struct regional*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrset_key_hash (TYPE_2__*) ; 
 int /*<<< orphan*/  synthesize_aaaa (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void
dns64_synth_aaaa_data(const struct ub_packed_rrset_key* fk, 
		      const struct packed_rrset_data* fd, 
		      struct ub_packed_rrset_key *dk, 
		      struct packed_rrset_data **dd_out, struct regional *region, 
		      struct dns64_env* dns64_env )
{
	struct packed_rrset_data *dd;
	size_t i;
	/*
	 * Create synthesized AAAA RR set data. We need to allocated extra memory
	 * for the RRs themselves. Each RR has a length, TTL, pointer to wireformat
	 * data, 2 bytes of data length, and 16 bytes of IPv6 address.
	 */
	if(fd->count > RR_COUNT_MAX) {
		*dd_out = NULL;
		return; /* integer overflow protection in alloc */
	}
	if (!(dd = *dd_out = regional_alloc(region,
		  sizeof(struct packed_rrset_data)
		  + fd->count * (sizeof(size_t) + sizeof(time_t) +
			     sizeof(uint8_t*) + 2 + 16)))) {
		log_err("out of memory");
		return;
	}

	/* Copy attributes from A RR set. */
	dd->ttl = fd->ttl;
	dd->count = fd->count;
	dd->rrsig_count = 0;
	dd->trust = fd->trust;
	dd->security = fd->security;

	/*
	 * Synthesize AAAA records. Adjust pointers in structure.
	 */
	dd->rr_len =
	    (size_t*)((uint8_t*)dd + sizeof(struct packed_rrset_data));
	dd->rr_data = (uint8_t**)&dd->rr_len[dd->count];
	dd->rr_ttl = (time_t*)&dd->rr_data[dd->count];
	for(i = 0; i < fd->count; ++i) {
		if (fd->rr_len[i] != 6 || fd->rr_data[i][0] != 0
		    || fd->rr_data[i][1] != 4) {
			*dd_out = NULL;
			return;
		}
		dd->rr_len[i] = 18;
		dd->rr_data[i] =
		    (uint8_t*)&dd->rr_ttl[dd->count] + 18*i;
		dd->rr_data[i][0] = 0;
		dd->rr_data[i][1] = 16;
		synthesize_aaaa(
				((struct sockaddr_in6*)&dns64_env->prefix_addr)->sin6_addr.s6_addr,
				dns64_env->prefix_net, &fd->rr_data[i][2],
				&dd->rr_data[i][2] );
		dd->rr_ttl[i] = fd->rr_ttl[i];
	}

	/*
	 * Create synthesized AAAA RR set key. This is mostly just bookkeeping,
	 * nothing interesting here.
	 */
	if(!dk) {
		log_err("no key");
		*dd_out = NULL;
		return;
	}

	dk->rk.dname = (uint8_t*)regional_alloc_init(region,
		     fk->rk.dname, fk->rk.dname_len);

	if(!dk->rk.dname) {
		log_err("out of memory");
		*dd_out = NULL;
		return;
	}

	dk->rk.type = htons(LDNS_RR_TYPE_AAAA);
	memset(&dk->entry, 0, sizeof(dk->entry));
	dk->entry.key = dk;
	dk->entry.hash = rrset_key_hash(&dk->rk);
	dk->entry.data = dd;

}