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
struct module_qstate {TYPE_2__* env; scalar_t__ errinf; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; int /*<<< orphan*/  hash; } ;
struct key_entry_key {TYPE_3__ entry; } ;
struct key_cache {int /*<<< orphan*/  slab; } ;
struct TYPE_5__ {TYPE_1__* cfg; } ;
struct TYPE_4__ {int val_log_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  errinf_to_str_bogus (struct module_qstate*) ; 
 struct key_entry_key* key_entry_copy (struct key_entry_key*) ; 
 int /*<<< orphan*/  key_entry_hash (struct key_entry_key*) ; 
 scalar_t__ key_entry_isbad (struct key_entry_key*) ; 
 int /*<<< orphan*/  key_entry_set_reason (struct key_entry_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slabhash_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void 
key_cache_insert(struct key_cache* kcache, struct key_entry_key* kkey,
	struct module_qstate* qstate)
{
	struct key_entry_key* k = key_entry_copy(kkey);
	if(!k)
		return;
	if(key_entry_isbad(k) && qstate->errinf &&
		qstate->env->cfg->val_log_level >= 2) {
		/* on malloc failure there is simply no reason string */
		key_entry_set_reason(k, errinf_to_str_bogus(qstate));
	}
	key_entry_hash(k);
	slabhash_insert(kcache->slab, k->entry.hash, &k->entry, 
		k->entry.data, NULL);
}