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
typedef  int /*<<< orphan*/ * lruhash_deldatafunc_type ;

/* Variables and functions */
 int /*<<< orphan*/  dnsc_nonces_deldatafunc ; 
 int /*<<< orphan*/  dnsc_shared_secrets_deldatafunc ; 
 int /*<<< orphan*/  infra_deldatafunc ; 
 int /*<<< orphan*/  key_entry_deldatafunc ; 
 int /*<<< orphan*/  rate_deldatafunc ; 
 int /*<<< orphan*/  reply_info_delete ; 
 int /*<<< orphan*/  rrset_data_delete ; 
 int /*<<< orphan*/  subnet_data_delete ; 
 int /*<<< orphan*/  test_slabhash_deldata ; 

int 
fptr_whitelist_hash_deldatafunc(lruhash_deldatafunc_type fptr)
{
	if(fptr == &reply_info_delete) return 1;
	else if(fptr == &rrset_data_delete) return 1;
	else if(fptr == &infra_deldatafunc) return 1;
	else if(fptr == &key_entry_deldatafunc) return 1;
	else if(fptr == &rate_deldatafunc) return 1;
	else if(fptr == &test_slabhash_deldata) return 1;
#ifdef CLIENT_SUBNET
	else if(fptr == &subnet_data_delete) return 1;
#endif
#ifdef USE_DNSCRYPT
	else if(fptr == &dnsc_shared_secrets_deldatafunc) return 1;
	else if(fptr == &dnsc_nonces_deldatafunc) return 1;
#endif
	return 0;
}