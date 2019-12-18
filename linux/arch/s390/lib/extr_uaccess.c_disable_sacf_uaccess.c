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
typedef  scalar_t__ mm_segment_t ;
struct TYPE_6__ {int /*<<< orphan*/  user_asce; } ;
struct TYPE_4__ {scalar_t__ mm_segment; } ;
struct TYPE_5__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIF_ASCE_PRIMARY ; 
 TYPE_3__ S390_lowcore ; 
 scalar_t__ USER_DS ; 
 int /*<<< orphan*/  __ctl_load (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  clear_cpu_flag (int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 scalar_t__ test_facility (int) ; 

void disable_sacf_uaccess(mm_segment_t old_fs)
{
	current->thread.mm_segment = old_fs;
	if (old_fs == USER_DS && test_facility(27)) {
		__ctl_load(S390_lowcore.user_asce, 1, 1);
		clear_cpu_flag(CIF_ASCE_PRIMARY);
	}
}