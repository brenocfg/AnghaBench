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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ipfw_flow_id {int dummy; } ;
struct ipfw_dyn_info {scalar_t__ direction; scalar_t__ hashval; scalar_t__ version; int /*<<< orphan*/  kidx; } ;
struct dyn_ipv4_state {void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CK_SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct dyn_ipv4_state*,int /*<<< orphan*/ ) ; 
 scalar_t__ DYN_BUCKET (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DYN_BUCKET_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  DYN_BUCKET_UNLOCK (scalar_t__) ; 
 scalar_t__ DYN_BUCKET_VERSION (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DYN_BUCKET_VERSION_BUMP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DYN_COUNT_INC (int /*<<< orphan*/ ) ; 
 int EEXIST ; 
 int ENOMEM ; 
 scalar_t__ MATCH_UNKNOWN ; 
 int /*<<< orphan*/  V_curr_dyn_buckets ; 
 int /*<<< orphan*/  V_dyn_data_zone ; 
 int /*<<< orphan*/ * V_dyn_ipv4 ; 
 void* dyn_alloc_dyndata (void*,scalar_t__,int /*<<< orphan*/ ,struct ipfw_flow_id const*,void const*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 struct dyn_ipv4_state* dyn_alloc_ipv4_state (struct ipfw_flow_id const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dyn_count ; 
 scalar_t__ dyn_lookup_ipv4_state_locked (struct ipfw_flow_id const*,void const*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  ipv4_add ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int
dyn_add_ipv4_state(void *parent, uint32_t ruleid, uint16_t rulenum,
    const struct ipfw_flow_id *pkt, const void *ulp, int pktlen,
    uint32_t hashval, struct ipfw_dyn_info *info, uint16_t fibnum,
    uint16_t kidx, uint8_t type)
{
	struct dyn_ipv4_state *s;
	void *data;
	uint32_t bucket;

	bucket = DYN_BUCKET(hashval, V_curr_dyn_buckets);
	DYN_BUCKET_LOCK(bucket);
	if (info->direction == MATCH_UNKNOWN ||
	    info->kidx != kidx ||
	    info->hashval != hashval ||
	    info->version != DYN_BUCKET_VERSION(bucket, ipv4_add)) {
		/*
		 * Bucket version has been changed since last lookup,
		 * do lookup again to be sure that state does not exist.
		 */
		if (dyn_lookup_ipv4_state_locked(pkt, ulp, pktlen,
		    bucket, kidx) != 0) {
			DYN_BUCKET_UNLOCK(bucket);
			return (EEXIST);
		}
	}

	data = dyn_alloc_dyndata(parent, ruleid, rulenum, pkt, ulp,
	    pktlen, hashval, fibnum);
	if (data == NULL) {
		DYN_BUCKET_UNLOCK(bucket);
		return (ENOMEM);
	}

	s = dyn_alloc_ipv4_state(pkt, kidx, type);
	if (s == NULL) {
		DYN_BUCKET_UNLOCK(bucket);
		uma_zfree(V_dyn_data_zone, data);
		return (ENOMEM);
	}

	s->data = data;
	CK_SLIST_INSERT_HEAD(&V_dyn_ipv4[bucket], s, entry);
	DYN_COUNT_INC(dyn_count);
	DYN_BUCKET_VERSION_BUMP(bucket, ipv4_add);
	DYN_BUCKET_UNLOCK(bucket);
	return (0);
}