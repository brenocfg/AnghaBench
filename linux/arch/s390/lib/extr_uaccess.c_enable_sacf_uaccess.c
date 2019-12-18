#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int mm_segment_t ;
struct TYPE_6__ {unsigned long kernel_asce; unsigned long user_asce; } ;
struct TYPE_4__ {int mm_segment; } ;
struct TYPE_5__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIF_ASCE_PRIMARY ; 
 int /*<<< orphan*/  CIF_ASCE_SECONDARY ; 
 TYPE_3__ S390_lowcore ; 
 int USER_DS ; 
 int /*<<< orphan*/  __ctl_load (unsigned long,int,int) ; 
 int /*<<< orphan*/  __ctl_store (unsigned long,int,int) ; 
 TYPE_2__* current ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  set_cpu_flag (int /*<<< orphan*/ ) ; 

mm_segment_t enable_sacf_uaccess(void)
{
	mm_segment_t old_fs;
	unsigned long asce, cr;

	old_fs = current->thread.mm_segment;
	if (old_fs & 1)
		return old_fs;
	current->thread.mm_segment |= 1;
	asce = S390_lowcore.kernel_asce;
	if (likely(old_fs == USER_DS)) {
		__ctl_store(cr, 1, 1);
		if (cr != S390_lowcore.kernel_asce) {
			__ctl_load(S390_lowcore.kernel_asce, 1, 1);
			set_cpu_flag(CIF_ASCE_PRIMARY);
		}
		asce = S390_lowcore.user_asce;
	}
	__ctl_store(cr, 7, 7);
	if (cr != asce) {
		__ctl_load(asce, 7, 7);
		set_cpu_flag(CIF_ASCE_SECONDARY);
	}
	return old_fs;
}