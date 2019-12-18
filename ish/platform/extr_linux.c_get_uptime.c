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
struct uptime_info {int /*<<< orphan*/  load_15m; int /*<<< orphan*/  load_5m; int /*<<< orphan*/  load_1m; int /*<<< orphan*/  uptime_ticks; } ;
struct sysinfo {int /*<<< orphan*/ * loads; int /*<<< orphan*/  uptime; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysinfo (struct sysinfo*) ; 

struct uptime_info get_uptime() {
    struct sysinfo info;
    sysinfo(&info);
    struct uptime_info uptime = {
        .uptime_ticks = info.uptime,
        .load_1m = info.loads[0],
        .load_5m = info.loads[1],
        .load_15m = info.loads[2],
    };
    return uptime;
}