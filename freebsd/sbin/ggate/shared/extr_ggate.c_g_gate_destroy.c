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
struct g_gate_ctl_destroy {int gctl_unit; int gctl_force; int /*<<< orphan*/  gctl_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_GATE_CMD_DESTROY ; 
 int /*<<< orphan*/  G_GATE_VERSION ; 
 int /*<<< orphan*/  g_gate_ioctl (int /*<<< orphan*/ ,struct g_gate_ctl_destroy*) ; 

void
g_gate_destroy(int unit, int force)
{
	struct g_gate_ctl_destroy ggio;

	ggio.gctl_version = G_GATE_VERSION;
	ggio.gctl_unit = unit;
	ggio.gctl_force = force;
	g_gate_ioctl(G_GATE_CMD_DESTROY, &ggio);
}