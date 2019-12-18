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
typedef  int /*<<< orphan*/ * lruhash_delkeyfunc_type ;

/* Variables and functions */
 int /*<<< orphan*/  dnsc_nonces_delkeyfunc ; 
 int /*<<< orphan*/  dnsc_shared_secrets_delkeyfunc ; 
 int /*<<< orphan*/  infra_delkeyfunc ; 
 int /*<<< orphan*/  ip_rate_delkeyfunc ; 
 int /*<<< orphan*/  key_entry_delkeyfunc ; 
 int /*<<< orphan*/  query_entry_delete ; 
 int /*<<< orphan*/  rate_delkeyfunc ; 
 int /*<<< orphan*/  test_slabhash_delkey ; 
 int /*<<< orphan*/  ub_rrset_key_delete ; 

int 
fptr_whitelist_hash_delkeyfunc(lruhash_delkeyfunc_type fptr)
{
	if(fptr == &query_entry_delete) return 1;
	else if(fptr == &ub_rrset_key_delete) return 1;
	else if(fptr == &infra_delkeyfunc) return 1;
	else if(fptr == &key_entry_delkeyfunc) return 1;
	else if(fptr == &rate_delkeyfunc) return 1;
	else if(fptr == &ip_rate_delkeyfunc) return 1;
	else if(fptr == &test_slabhash_delkey) return 1;
#ifdef USE_DNSCRYPT
	else if(fptr == &dnsc_shared_secrets_delkeyfunc) return 1;
	else if(fptr == &dnsc_nonces_delkeyfunc) return 1;
#endif
	return 0;
}