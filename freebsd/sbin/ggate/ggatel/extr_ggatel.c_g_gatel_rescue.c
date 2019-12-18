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
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  G_GATE_CMD_CANCEL ; 
 int /*<<< orphan*/  G_GATE_VERSION ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  g_gate_ioctl (int /*<<< orphan*/ ,struct g_gate_ctl_cancel*) ; 
 int /*<<< orphan*/  g_gate_openflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_gatel_serve (int) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path ; 
 int /*<<< orphan*/  unit ; 

__attribute__((used)) static void
g_gatel_rescue(void)
{
	struct g_gate_ctl_cancel ggioc;
	int fd;

	fd = open(path, g_gate_openflags(flags));
	if (fd == -1)
		err(EXIT_FAILURE, "Cannot open %s", path);

	ggioc.gctl_version = G_GATE_VERSION;
	ggioc.gctl_unit = unit;
	ggioc.gctl_seq = 0;
	g_gate_ioctl(G_GATE_CMD_CANCEL, &ggioc);

	g_gatel_serve(fd);
}