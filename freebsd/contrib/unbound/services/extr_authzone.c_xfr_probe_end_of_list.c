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
struct auth_xfer {TYPE_1__* task_probe; } ;
struct TYPE_2__ {int /*<<< orphan*/  scan_target; int /*<<< orphan*/  scan_specific; } ;

/* Variables and functions */

__attribute__((used)) static int
xfr_probe_end_of_list(struct auth_xfer* xfr)
{
	return !xfr->task_probe->scan_specific && !xfr->task_probe->scan_target;
}