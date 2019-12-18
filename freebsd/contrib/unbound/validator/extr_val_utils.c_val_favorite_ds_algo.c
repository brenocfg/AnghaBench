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

/* Variables and functions */
 int /*<<< orphan*/  ds_digest_algo_is_supported (struct ub_packed_rrset_key*,size_t) ; 
 int ds_get_digest_algo (struct ub_packed_rrset_key*,size_t) ; 
 int /*<<< orphan*/  ds_key_algo_is_supported (struct ub_packed_rrset_key*,size_t) ; 
 size_t rrset_get_count (struct ub_packed_rrset_key*) ; 

int val_favorite_ds_algo(struct ub_packed_rrset_key* ds_rrset)
{
	size_t i, num = rrset_get_count(ds_rrset);
	int d, digest_algo = 0; /* DS digest algo 0 is not used. */
	/* find favorite algo, for now, highest number supported */
	for(i=0; i<num; i++) {
		if(!ds_digest_algo_is_supported(ds_rrset, i) ||
			!ds_key_algo_is_supported(ds_rrset, i)) {
			continue;
		}
		d = ds_get_digest_algo(ds_rrset, i);
		if(d > digest_algo)
			digest_algo = d;
	}
	return digest_algo;
}