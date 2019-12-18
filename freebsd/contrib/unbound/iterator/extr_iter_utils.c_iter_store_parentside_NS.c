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
struct ub_packed_rrset_key {int dummy; } ;
struct reply_info {int dummy; } ;
struct module_env {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  iter_store_parentside_rrset (struct module_env*,struct ub_packed_rrset_key*) ; 
 int /*<<< orphan*/  log_rrset_key (int /*<<< orphan*/ ,char*,struct ub_packed_rrset_key*) ; 
 struct ub_packed_rrset_key* reply_get_NS_rrset (struct reply_info*) ; 

void
iter_store_parentside_NS(struct module_env* env, struct reply_info* rep)
{
	struct ub_packed_rrset_key* rrset = reply_get_NS_rrset(rep);
	if(rrset) {
		log_rrset_key(VERB_ALGO, "store parent-side NS", rrset);
		iter_store_parentside_rrset(env, rrset);
	}
}