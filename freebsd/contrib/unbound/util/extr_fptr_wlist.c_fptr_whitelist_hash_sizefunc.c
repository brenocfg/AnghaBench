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
typedef  int /*<<< orphan*/ * lruhash_sizefunc_type ;

/* Variables and functions */
 int /*<<< orphan*/  dnsc_nonces_sizefunc ; 
 int /*<<< orphan*/  dnsc_shared_secrets_sizefunc ; 
 int /*<<< orphan*/  infra_sizefunc ; 
 int /*<<< orphan*/  ip_rate_sizefunc ; 
 int /*<<< orphan*/  key_entry_sizefunc ; 
 int /*<<< orphan*/  msg_cache_sizefunc ; 
 int /*<<< orphan*/  msgreply_sizefunc ; 
 int /*<<< orphan*/  rate_sizefunc ; 
 int /*<<< orphan*/  test_slabhash_sizefunc ; 
 int /*<<< orphan*/  ub_rrset_sizefunc ; 

int 
fptr_whitelist_hash_sizefunc(lruhash_sizefunc_type fptr)
{
	if(fptr == &msgreply_sizefunc) return 1;
	else if(fptr == &ub_rrset_sizefunc) return 1;
	else if(fptr == &infra_sizefunc) return 1;
	else if(fptr == &key_entry_sizefunc) return 1;
	else if(fptr == &rate_sizefunc) return 1;
	else if(fptr == &ip_rate_sizefunc) return 1;
	else if(fptr == &test_slabhash_sizefunc) return 1;
#ifdef CLIENT_SUBNET
	else if(fptr == &msg_cache_sizefunc) return 1;
#endif
#ifdef USE_DNSCRYPT
	else if(fptr == &dnsc_shared_secrets_sizefunc) return 1;
	else if(fptr == &dnsc_nonces_sizefunc) return 1;
#endif
	return 0;
}