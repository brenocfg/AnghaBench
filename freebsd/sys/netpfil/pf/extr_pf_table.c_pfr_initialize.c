#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pfr_kentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  limit; int /*<<< orphan*/  zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFR_KENTRY_HIWAT ; 
 size_t PF_LIMIT_TABLE_ENTRIES ; 
 int /*<<< orphan*/  UMA_ALIGN_PTR ; 
 TYPE_1__* V_pf_limits ; 
 int /*<<< orphan*/  V_pfr_kentry_z ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pfr_initialize(void)
{

	V_pfr_kentry_z = uma_zcreate("pf table entries",
	    sizeof(struct pfr_kentry), NULL, NULL, NULL, NULL, UMA_ALIGN_PTR,
	    0);
	V_pf_limits[PF_LIMIT_TABLE_ENTRIES].zone = V_pfr_kentry_z;
	V_pf_limits[PF_LIMIT_TABLE_ENTRIES].limit = PFR_KENTRY_HIWAT;
}