#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  tz_dsttime; int /*<<< orphan*/  tz_minuteswest; } ;
struct TYPE_4__ {int /*<<< orphan*/  tz_dsttime; int /*<<< orphan*/  tz_minuteswest; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_dcache_page (int /*<<< orphan*/ ) ; 
 TYPE_3__ sys_tz ; 
 TYPE_1__* vdso_data ; 
 int /*<<< orphan*/  virt_to_page (TYPE_1__*) ; 

void update_vsyscall_tz(void)
{
	vdso_data->tz_minuteswest	= sys_tz.tz_minuteswest;
	vdso_data->tz_dsttime		= sys_tz.tz_dsttime;
	flush_dcache_page(virt_to_page(vdso_data));
}