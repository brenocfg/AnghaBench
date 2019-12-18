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
struct ucred {int cr_agroups; scalar_t__* cr_groups; int cr_ngroups; } ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  bcopy (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static void
crsetgroups_locked(struct ucred *cr, int ngrp, gid_t *groups)
{
	int i;
	int j;
	gid_t g;
	
	KASSERT(cr->cr_agroups >= ngrp, ("cr_ngroups is too small"));

	bcopy(groups, cr->cr_groups, ngrp * sizeof(gid_t));
	cr->cr_ngroups = ngrp;

	/*
	 * Sort all groups except cr_groups[0] to allow groupmember to
	 * perform a binary search.
	 *
	 * XXX: If large numbers of groups become common this should
	 * be replaced with shell sort like linux uses or possibly
	 * heap sort.
	 */
	for (i = 2; i < ngrp; i++) {
		g = cr->cr_groups[i];
		for (j = i-1; j >= 1 && g < cr->cr_groups[j]; j--)
			cr->cr_groups[j + 1] = cr->cr_groups[j];
		cr->cr_groups[j + 1] = g;
	}
}