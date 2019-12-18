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
struct val_env {int dummy; } ;
struct ub_packed_rrset_key {int dummy; } ;
struct module_qstate {int dummy; } ;
struct module_env {int dummy; } ;
typedef  enum sec_status { ____Placeholder_sec_status } sec_status ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_SECTION_ANSWER ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int dnskey_verify_rrset (struct module_env*,struct val_env*,struct ub_packed_rrset_key*,struct ub_packed_rrset_key*,size_t,char**,int /*<<< orphan*/ ,struct module_qstate*) ; 
 int sec_status_secure ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
rr_is_selfsigned_revoked(struct module_env* env, struct val_env* ve,
	struct ub_packed_rrset_key* dnskey_rrset, size_t i,
	struct module_qstate* qstate)
{
	enum sec_status sec;
	char* reason = NULL;
	verbose(VERB_ALGO, "seen REVOKE flag, check self-signed, rr %d",
		(int)i);
	/* no algorithm downgrade protection necessary, if it is selfsigned
	 * revoked it can be removed. */
	sec = dnskey_verify_rrset(env, ve, dnskey_rrset, dnskey_rrset, i, 
		&reason, LDNS_SECTION_ANSWER, qstate);
	return (sec == sec_status_secure);
}