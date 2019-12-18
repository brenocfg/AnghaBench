#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_3__ {scalar_t__ gidset_size; int /*<<< orphan*/ * gidset; } ;
struct TYPE_4__ {TYPE_1__ ar_arg_groups; } ;
struct kaudit_record {TYPE_2__ k_ar; } ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_GROUPSET ; 
 int /*<<< orphan*/  ARG_SET_VALID (struct kaudit_record*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_AUDITGIDSET ; 
 int /*<<< orphan*/  M_WAITOK ; 
 struct kaudit_record* currecord () ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngroups_max ; 

void
audit_arg_groupset(gid_t *gidset, u_int gidset_size)
{
	u_int i;
	struct kaudit_record *ar;

	KASSERT(gidset_size <= ngroups_max + 1,
	    ("audit_arg_groupset: gidset_size > (kern.ngroups + 1)"));

	ar = currecord();
	if (ar == NULL)
		return;

	if (ar->k_ar.ar_arg_groups.gidset == NULL)
		ar->k_ar.ar_arg_groups.gidset = malloc(
		    sizeof(gid_t) * gidset_size, M_AUDITGIDSET, M_WAITOK);

	for (i = 0; i < gidset_size; i++)
		ar->k_ar.ar_arg_groups.gidset[i] = gidset[i];
	ar->k_ar.ar_arg_groups.gidset_size = gidset_size;
	ARG_SET_VALID(ar, ARG_GROUPSET);
}