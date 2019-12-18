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
struct cpu_usage {int /*<<< orphan*/  nice_ticks; int /*<<< orphan*/  idle_ticks; int /*<<< orphan*/  system_ticks; int /*<<< orphan*/  user_ticks; } ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  host_info_t ;
struct TYPE_2__ {int /*<<< orphan*/ * cpu_ticks; } ;
typedef  TYPE_1__ host_cpu_load_info_data_t ;

/* Variables and functions */
 size_t CPU_STATE_IDLE ; 
 size_t CPU_STATE_NICE ; 
 size_t CPU_STATE_SYSTEM ; 
 size_t CPU_STATE_USER ; 
 int /*<<< orphan*/  HOST_CPU_LOAD_INFO ; 
 int /*<<< orphan*/  HOST_CPU_LOAD_INFO_COUNT ; 
 int /*<<< orphan*/  host_statistics (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mach_host_self () ; 

struct cpu_usage get_cpu_usage() {
    host_cpu_load_info_data_t load;
    mach_msg_type_number_t fuck = HOST_CPU_LOAD_INFO_COUNT;
    host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t) &load, &fuck);
    struct cpu_usage usage;
    usage.user_ticks = load.cpu_ticks[CPU_STATE_USER];
    usage.system_ticks = load.cpu_ticks[CPU_STATE_SYSTEM];
    usage.idle_ticks = load.cpu_ticks[CPU_STATE_IDLE];
    usage.nice_ticks = load.cpu_ticks[CPU_STATE_NICE];
    return usage;
}