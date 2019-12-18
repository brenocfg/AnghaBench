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

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  G_GATE_CTL_NAME ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  g_gate_cdevsw ; 
 int /*<<< orphan*/  make_dev (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status_dev ; 

__attribute__((used)) static void
g_gate_device(void)
{

	status_dev = make_dev(&g_gate_cdevsw, 0x0, UID_ROOT, GID_WHEEL, 0600,
	    G_GATE_CTL_NAME);
}