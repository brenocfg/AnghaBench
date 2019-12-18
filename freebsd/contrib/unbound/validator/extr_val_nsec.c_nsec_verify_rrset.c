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
struct val_env {int dummy; } ;
struct TYPE_2__ {scalar_t__ data; } ;
struct ub_packed_rrset_key {TYPE_1__ entry; } ;
struct packed_rrset_data {scalar_t__ security; } ;
struct module_qstate {int dummy; } ;
struct module_env {int /*<<< orphan*/ * now; int /*<<< orphan*/  rrset_cache; } ;
struct key_entry_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_SECTION_AUTHORITY ; 
 int /*<<< orphan*/  rrset_check_sec_status (int /*<<< orphan*/ ,struct ub_packed_rrset_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rrset_update_sec_status (int /*<<< orphan*/ ,struct ub_packed_rrset_key*,int /*<<< orphan*/ ) ; 
 scalar_t__ sec_status_secure ; 
 scalar_t__ val_verify_rrset_entry (struct module_env*,struct val_env*,struct ub_packed_rrset_key*,struct key_entry_key*,char**,int /*<<< orphan*/ ,struct module_qstate*) ; 

__attribute__((used)) static int
nsec_verify_rrset(struct module_env* env, struct val_env* ve, 
	struct ub_packed_rrset_key* nsec, struct key_entry_key* kkey, 
	char** reason, struct module_qstate* qstate)
{
	struct packed_rrset_data* d = (struct packed_rrset_data*)
		nsec->entry.data;
	if(d->security == sec_status_secure)
		return 1;
	rrset_check_sec_status(env->rrset_cache, nsec, *env->now);
	if(d->security == sec_status_secure)
		return 1;
	d->security = val_verify_rrset_entry(env, ve, nsec, kkey, reason,
		LDNS_SECTION_AUTHORITY, qstate);
	if(d->security == sec_status_secure) {
		rrset_update_sec_status(env->rrset_cache, nsec, *env->now);
		return 1;
	}
	return 0;
}