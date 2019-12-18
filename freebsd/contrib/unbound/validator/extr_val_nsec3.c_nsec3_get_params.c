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
typedef  int /*<<< orphan*/  uint8_t ;
struct ub_packed_rrset_key {int dummy; } ;

/* Variables and functions */
 int nsec3_get_algo (struct ub_packed_rrset_key*,int) ; 
 size_t nsec3_get_iter (struct ub_packed_rrset_key*,int) ; 
 int /*<<< orphan*/  nsec3_get_salt (struct ub_packed_rrset_key*,int,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  nsec3_known_algo (struct ub_packed_rrset_key*,int) ; 
 scalar_t__ nsec3_unknown_flags (struct ub_packed_rrset_key*,int) ; 

int nsec3_get_params(struct ub_packed_rrset_key* rrset, int r,
	int* algo, size_t* iter, uint8_t** salt, size_t* saltlen)
{
	if(!nsec3_known_algo(rrset, r) || nsec3_unknown_flags(rrset, r))
		return 0;
	if(!nsec3_get_salt(rrset, r, salt, saltlen))
		return 0;
	*algo = nsec3_get_algo(rrset, r);
	*iter = nsec3_get_iter(rrset, r);
	return 1;
}