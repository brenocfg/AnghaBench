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
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
struct ub_packed_rrset_key {int /*<<< orphan*/  id; TYPE_1__ entry; } ;
struct rrset_ref {int /*<<< orphan*/  id; struct ub_packed_rrset_key* key; } ;
struct rrset_parse {int dummy; } ;
struct packed_rrset_data {int dummy; } ;
struct msg_parse {int dummy; } ;
struct module_env {int /*<<< orphan*/  alloc; int /*<<< orphan*/  rrset_cache; int /*<<< orphan*/ * now; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 struct ub_packed_rrset_key* alloc_special_obtain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alloc_special_release (int /*<<< orphan*/ ,struct ub_packed_rrset_key*) ; 
 int /*<<< orphan*/  packed_rrset_ttl_add (struct packed_rrset_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_copy_decompress_rrset (int /*<<< orphan*/ *,struct msg_parse*,struct rrset_parse*,int /*<<< orphan*/ *,struct ub_packed_rrset_key*) ; 
 int /*<<< orphan*/  rrset_cache_update (int /*<<< orphan*/ ,struct rrset_ref*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
store_rrset(sldns_buffer* pkt, struct msg_parse* msg, struct module_env* env,
	struct rrset_parse* rrset)
{
	struct ub_packed_rrset_key* k;
	struct packed_rrset_data* d;
	struct rrset_ref ref;
	time_t now = *env->now;

	k = alloc_special_obtain(env->alloc);
	if(!k)
		return;
	k->entry.data = NULL;
	if(!parse_copy_decompress_rrset(pkt, msg, rrset, NULL, k)) {
		alloc_special_release(env->alloc, k);
		return;
	}
	d = (struct packed_rrset_data*)k->entry.data;
	packed_rrset_ttl_add(d, now);
	ref.key = k;
	ref.id = k->id;
	/*ignore ret: it was in the cache, ref updated */
	(void)rrset_cache_update(env->rrset_cache, &ref, env->alloc, now);
}