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
struct sysinfo_3_2_2 {int /*<<< orphan*/  count; TYPE_2__* vm; } ;
struct lgr_info {int /*<<< orphan*/  vm_count; TYPE_1__* vm; } ;
struct TYPE_4__ {int /*<<< orphan*/  cpi; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpi; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_LEVEL_MAX ; 
 int /*<<< orphan*/  cpascii (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lgr_page ; 
 int min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stsi (struct sysinfo_3_2_2*,int,int,int) ; 
 int /*<<< orphan*/  u8 ; 

__attribute__((used)) static void lgr_stsi_3_2_2(struct lgr_info *lgr_info)
{
	struct sysinfo_3_2_2 *si = (void *) lgr_page;
	int i;

	if (stsi(si, 3, 2, 2))
		return;
	for (i = 0; i < min_t(u8, si->count, VM_LEVEL_MAX); i++) {
		cpascii(lgr_info->vm[i].name, si->vm[i].name,
			sizeof(si->vm[i].name));
		cpascii(lgr_info->vm[i].cpi, si->vm[i].cpi,
			sizeof(si->vm[i].cpi));
	}
	lgr_info->vm_count = si->count;
}