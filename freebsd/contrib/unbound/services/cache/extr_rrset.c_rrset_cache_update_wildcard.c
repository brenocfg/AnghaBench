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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_4__ {int* dname; size_t dname_len; } ;
struct TYPE_3__ {int /*<<< orphan*/  hash; } ;
struct ub_packed_rrset_key {int /*<<< orphan*/  id; TYPE_2__ rk; TYPE_1__ entry; } ;
struct rrset_ref {int /*<<< orphan*/  id; struct ub_packed_rrset_key* key; } ;
struct rrset_cache {int dummy; } ;
struct alloc_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_DOMAINLEN ; 
 int /*<<< orphan*/  alloc_special_release (struct alloc_cache*,struct ub_packed_rrset_key*) ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ memdup (int*,size_t) ; 
 int /*<<< orphan*/  memmove (int*,int*,size_t) ; 
 struct ub_packed_rrset_key* packed_rrset_copy_alloc (struct ub_packed_rrset_key*,struct alloc_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrset_cache_update (struct rrset_cache*,struct rrset_ref*,struct alloc_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrset_key_hash (TYPE_2__*) ; 

void rrset_cache_update_wildcard(struct rrset_cache* rrset_cache, 
	struct ub_packed_rrset_key* rrset, uint8_t* ce, size_t ce_len,
	struct alloc_cache* alloc, time_t timenow)
{
	struct rrset_ref ref;
	uint8_t wc_dname[LDNS_MAX_DOMAINLEN+3];
	rrset = packed_rrset_copy_alloc(rrset, alloc, timenow);
	if(!rrset) {
		log_err("malloc failure in rrset_cache_update_wildcard");
		return;
	}
	/* ce has at least one label less then qname, we can therefore safely
	 * add the wildcard label. */
	wc_dname[0] = 1;
	wc_dname[1] = (uint8_t)'*';
	memmove(wc_dname+2, ce, ce_len);

	free(rrset->rk.dname);
	rrset->rk.dname_len = ce_len + 2;
	rrset->rk.dname = (uint8_t*)memdup(wc_dname, rrset->rk.dname_len);
	if(!rrset->rk.dname) {
		alloc_special_release(alloc, rrset);
		log_err("memdup failure in rrset_cache_update_wildcard");
		return;
	}

	rrset->entry.hash = rrset_key_hash(&rrset->rk);
	ref.key = rrset;
	ref.id = rrset->id;
	/* ignore ret: if it was in the cache, ref updated */
	(void)rrset_cache_update(rrset_cache, &ref, alloc, timenow);
}