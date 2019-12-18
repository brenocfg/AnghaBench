#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ proc_task; } ;
struct TYPE_5__ {TYPE_1__ daemon_sc; int /*<<< orphan*/  register_done; } ;
typedef  TYPE_2__ hv_vss_sc ;

/* Variables and functions */

__attribute__((used)) static bool
hv_vss_is_daemon_killed_after_launch(hv_vss_sc *sc)
{
	return (!sc->register_done && sc->daemon_sc.proc_task);
}