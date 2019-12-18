#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sysinfo {int /*<<< orphan*/  mem_unit; int /*<<< orphan*/  freehigh; int /*<<< orphan*/  totalhigh; int /*<<< orphan*/  procs; int /*<<< orphan*/  freeswap; int /*<<< orphan*/  totalswap; int /*<<< orphan*/  sharedram; int /*<<< orphan*/  freeram; int /*<<< orphan*/  totalram; } ;
struct sys_info {int /*<<< orphan*/  mem_unit; int /*<<< orphan*/  freehigh; int /*<<< orphan*/  totalhigh; int /*<<< orphan*/  procs; int /*<<< orphan*/  freeswap; int /*<<< orphan*/  totalswap; int /*<<< orphan*/  sharedram; int /*<<< orphan*/  freeram; int /*<<< orphan*/  totalram; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysinfo (struct sysinfo*) ; 

__attribute__((used)) static void sysinfo_specific(struct sys_info *info) {
    struct sysinfo host_info;
    sysinfo(&host_info);
    info->totalram = host_info.totalram;
    info->freeram = host_info.freeram;
    info->sharedram = host_info.sharedram;
    info->totalswap = host_info.totalswap;
    info->freeswap = host_info.freeswap;
    info->procs = host_info.procs;
    info->totalhigh = host_info.totalhigh;
    info->freehigh = host_info.freehigh;
    info->mem_unit = host_info.mem_unit;
}