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
typedef  int /*<<< orphan*/ * lruhash_compfunc_type ;

/* Variables and functions */
 int /*<<< orphan*/  dnsc_nonces_compfunc ; 
 int /*<<< orphan*/  dnsc_shared_secrets_compfunc ; 
 int /*<<< orphan*/  infra_compfunc ; 
 int /*<<< orphan*/  ip_rate_compfunc ; 
 int /*<<< orphan*/  key_entry_compfunc ; 
 int /*<<< orphan*/  query_info_compare ; 
 int /*<<< orphan*/  rate_compfunc ; 
 int /*<<< orphan*/  test_slabhash_compfunc ; 
 int /*<<< orphan*/  ub_rrset_compare ; 

int 
fptr_whitelist_hash_compfunc(lruhash_compfunc_type fptr)
{
	if(fptr == &query_info_compare) return 1;
	else if(fptr == &ub_rrset_compare) return 1;
	else if(fptr == &infra_compfunc) return 1;
	else if(fptr == &key_entry_compfunc) return 1;
	else if(fptr == &rate_compfunc) return 1;
	else if(fptr == &ip_rate_compfunc) return 1;
	else if(fptr == &test_slabhash_compfunc) return 1;
#ifdef USE_DNSCRYPT
	else if(fptr == &dnsc_shared_secrets_compfunc) return 1;
	else if(fptr == &dnsc_nonces_compfunc) return 1;
#endif
	return 0;
}