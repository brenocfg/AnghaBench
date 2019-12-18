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
typedef  size_t ldns_signing_algorithm ;
typedef  int /*<<< orphan*/  ldns_key_list ;
typedef  int /*<<< orphan*/  ldns_key ;

/* Variables and functions */
 int LDNS_KEY_SEP_KEY ; 
 int LDNS_SIGN_WITH_ALL_ALGORITHMS ; 
 size_t ldns_key_algorithm (int /*<<< orphan*/ *) ; 
 int ldns_key_flags (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_key_list_key (int /*<<< orphan*/ *,size_t) ; 
 size_t ldns_key_list_key_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_key_set_use (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ldns_key_list_filter_for_dnskey(ldns_key_list *key_list, int flags)
{
	bool algos[256]
#ifndef S_SPLINT_S
	                = { false }
#endif
	                           ;
	ldns_signing_algorithm saw_ksk = 0;
	ldns_key *key;
	size_t i;

	if (!ldns_key_list_key_count(key_list))
		return;

	for (i = 0; i < ldns_key_list_key_count(key_list); i++) {
		key = ldns_key_list_key(key_list, i);
		if ((ldns_key_flags(key) & LDNS_KEY_SEP_KEY) && !saw_ksk)
			saw_ksk = ldns_key_algorithm(key);
		algos[ldns_key_algorithm(key)] = true;
	}
	if (!saw_ksk)
		return;
	else
		algos[saw_ksk] = 0;

	for (i =0; i < ldns_key_list_key_count(key_list); i++) {
		key = ldns_key_list_key(key_list, i);
		if (!(ldns_key_flags(key) & LDNS_KEY_SEP_KEY)) {
			/* We have a ZSK.
			 * Still use it if it has a unique algorithm though!
			 */
			if ((flags & LDNS_SIGN_WITH_ALL_ALGORITHMS) &&
			    algos[ldns_key_algorithm(key)])
				algos[ldns_key_algorithm(key)] = false;
			else
				ldns_key_set_use(key, 0);
		}
	}
}