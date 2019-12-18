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
typedef  scalar_t__ u16 ;
struct mem_ctl_info {int tot_dimms; TYPE_1__** dimms; } ;
struct TYPE_4__ {struct mem_ctl_info* mci; } ;
struct TYPE_3__ {scalar_t__ smbios_handle; } ;

/* Variables and functions */
 TYPE_2__* ghes_pvt ; 

__attribute__((used)) static int get_dimm_smbios_index(u16 handle)
{
	struct mem_ctl_info *mci = ghes_pvt->mci;
	int i;

	for (i = 0; i < mci->tot_dimms; i++) {
		if (mci->dimms[i]->smbios_handle == handle)
			return i;
	}
	return -1;
}