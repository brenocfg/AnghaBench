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
struct g_gate_ctl_cancel {scalar_t__ gctl_seq; int /*<<< orphan*/  gctl_unit; int /*<<< orphan*/  gctl_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_GATE_CMD_CANCEL ; 
 int /*<<< orphan*/  G_GATE_VERSION ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  g_gate_ioctl (int /*<<< orphan*/ ,struct g_gate_ctl_cancel*) ; 
 int /*<<< orphan*/  g_gate_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_gatec_connect () ; 
 int /*<<< orphan*/  g_gatec_start () ; 
 int /*<<< orphan*/  host ; 
 int /*<<< orphan*/  path ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signop ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  unit ; 

__attribute__((used)) static void
g_gatec_loop(void)
{
	struct g_gate_ctl_cancel ggioc;

	signal(SIGUSR1, signop);
	for (;;) {
		g_gatec_start();
		g_gate_log(LOG_NOTICE, "Disconnected [%s %s]. Connecting...",
		    host, path);
		while (!g_gatec_connect()) {
			sleep(2);
			g_gate_log(LOG_NOTICE, "Connecting [%s %s]...", host,
			    path);
		}
		ggioc.gctl_version = G_GATE_VERSION;
		ggioc.gctl_unit = unit;
		ggioc.gctl_seq = 0;
		g_gate_ioctl(G_GATE_CMD_CANCEL, &ggioc);
	}
}