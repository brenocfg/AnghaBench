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
struct sysinfo_3_2_2 {TYPE_1__* vm; int /*<<< orphan*/  count; } ;
struct TYPE_4__ {int /*<<< orphan*/  machine_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  cpi; } ;

/* Variables and functions */
 int /*<<< orphan*/  MACHINE_FLAG_KVM ; 
 int /*<<< orphan*/  MACHINE_FLAG_LPAR ; 
 int /*<<< orphan*/  MACHINE_FLAG_VM ; 
 TYPE_2__ S390_lowcore ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int stsi (struct sysinfo_3_2_2*,int,int,int) ; 
 int /*<<< orphan*/  sysinfo_page ; 

void detect_machine_type(void)
{
	struct sysinfo_3_2_2 *vmms = (struct sysinfo_3_2_2 *)&sysinfo_page;

	/* Check current-configuration-level */
	if (stsi(NULL, 0, 0, 0) <= 2) {
		S390_lowcore.machine_flags |= MACHINE_FLAG_LPAR;
		return;
	}
	/* Get virtual-machine cpu information. */
	if (stsi(vmms, 3, 2, 2) || !vmms->count)
		return;

	/* Detect known hypervisors */
	if (!memcmp(vmms->vm[0].cpi, "\xd2\xe5\xd4", 3))
		S390_lowcore.machine_flags |= MACHINE_FLAG_KVM;
	else if (!memcmp(vmms->vm[0].cpi, "\xa9\x61\xe5\xd4", 4))
		S390_lowcore.machine_flags |= MACHINE_FLAG_VM;
}