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
struct nsec3_filter {int dummy; } ;
struct key_entry_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 struct ub_packed_rrset_key* filter_first (struct nsec3_filter*,size_t*,int*) ; 
 struct ub_packed_rrset_key* filter_next (struct nsec3_filter*,size_t*,int*) ; 
 size_t get_max_iter (struct val_env*,size_t) ; 
 size_t key_entry_keysize (struct key_entry_key*) ; 
 size_t nsec3_get_iter (struct ub_packed_rrset_key*,int) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int
nsec3_iteration_count_high(struct val_env* ve, struct nsec3_filter* filter, 
	struct key_entry_key* kkey)
{
	size_t rrsetnum;
	int rrnum;
	struct ub_packed_rrset_key* rrset;
	/* first determine the max number of iterations */
	size_t bits = key_entry_keysize(kkey);
	size_t max_iter = get_max_iter(ve, bits);
	verbose(VERB_ALGO, "nsec3: keysize %d bits, max iterations %d",
		(int)bits, (int)max_iter);

	for(rrset=filter_first(filter, &rrsetnum, &rrnum); rrset; 
		rrset=filter_next(filter, &rrsetnum, &rrnum)) {
		if(nsec3_get_iter(rrset, rrnum) > max_iter)
			return 1;
	}
	return 0;
}