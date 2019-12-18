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
struct val_env {int dummy; } ;
struct TYPE_4__ {scalar_t__ type; } ;
struct TYPE_3__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_2__ rk; TYPE_1__ entry; } ;
struct packed_rrset_data {scalar_t__ security; } ;
struct module_qstate {int dummy; } ;
struct module_env {int /*<<< orphan*/ * now; int /*<<< orphan*/  rrset_cache; } ;
struct key_entry_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_RR_TYPE_NSEC3 ; 
 int /*<<< orphan*/  LDNS_SECTION_AUTHORITY ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrset_check_sec_status (int /*<<< orphan*/ ,struct ub_packed_rrset_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrset_update_sec_status (int /*<<< orphan*/ ,struct ub_packed_rrset_key*,int /*<<< orphan*/ ) ; 
 scalar_t__ sec_status_secure ; 
 scalar_t__ val_verify_rrset_entry (struct module_env*,struct val_env*,struct ub_packed_rrset_key*,struct key_entry_key*,char**,int /*<<< orphan*/ ,struct module_qstate*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
list_is_secure(struct module_env* env, struct val_env* ve, 
	struct ub_packed_rrset_key** list, size_t num,
	struct key_entry_key* kkey, char** reason, struct module_qstate* qstate)
{
	struct packed_rrset_data* d;
	size_t i;
	for(i=0; i<num; i++) {
		d = (struct packed_rrset_data*)list[i]->entry.data;
		if(list[i]->rk.type != htons(LDNS_RR_TYPE_NSEC3))
			continue;
		if(d->security == sec_status_secure)
			continue;
		rrset_check_sec_status(env->rrset_cache, list[i], *env->now);
		if(d->security == sec_status_secure)
			continue;
		d->security = val_verify_rrset_entry(env, ve, list[i], kkey,
			reason, LDNS_SECTION_AUTHORITY, qstate);
		if(d->security != sec_status_secure) {
			verbose(VERB_ALGO, "NSEC3 did not verify");
			return 0;
		}
		rrset_update_sec_status(env->rrset_cache, list[i], *env->now);
	}
	return 1;
}