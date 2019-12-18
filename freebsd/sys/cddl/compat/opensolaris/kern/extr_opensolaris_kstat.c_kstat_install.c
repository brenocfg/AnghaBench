#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
struct TYPE_5__ {scalar_t__ ks_ndata; int /*<<< orphan*/  ks_sysctl_root; int /*<<< orphan*/  ks_sysctl_ctx; TYPE_2__* ks_data; } ;
typedef  TYPE_1__ kstat_t ;
struct TYPE_6__ {scalar_t__ data_type; int /*<<< orphan*/  desc; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ kstat_named_t ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLTYPE_U64 ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ KSTAT_DATA_UINT64 ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstat_sysctl ; 

void
kstat_install(kstat_t *ksp)
{
	kstat_named_t *ksent;
	u_int i;

	ksent = ksp->ks_data;
	for (i = 0; i < ksp->ks_ndata; i++, ksent++) {
		KASSERT(ksent->data_type == KSTAT_DATA_UINT64,
		    ("data_type=%d", ksent->data_type));
		SYSCTL_ADD_PROC(&ksp->ks_sysctl_ctx,
		    SYSCTL_CHILDREN(ksp->ks_sysctl_root), OID_AUTO, ksent->name,
		    CTLTYPE_U64 | CTLFLAG_RD, ksent, sizeof(*ksent),
		    kstat_sysctl, "QU", ksent->desc);
	}
}