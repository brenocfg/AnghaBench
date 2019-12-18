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
struct g_gate_ctl_create {int gctl_unit; int /*<<< orphan*/  gctl_info; scalar_t__ gctl_maxcount; int /*<<< orphan*/  gctl_flags; int /*<<< orphan*/  gctl_timeout; scalar_t__ gctl_sectorsize; int /*<<< orphan*/  gctl_mediasize; int /*<<< orphan*/  gctl_version; } ;
typedef  int /*<<< orphan*/  ggioc ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  G_GATE_CMD_CREATE ; 
 char* G_GATE_PROVIDER_NAME ; 
 int /*<<< orphan*/  G_GATE_VERSION ; 
 int O_DIRECT ; 
 int O_FSYNC ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  g_gate_ioctl (int /*<<< orphan*/ ,struct g_gate_ctl_create*) ; 
 int /*<<< orphan*/  g_gate_mediasize (int) ; 
 int g_gate_openflags (int /*<<< orphan*/ ) ; 
 scalar_t__ g_gate_sectorsize (int) ; 
 int /*<<< orphan*/  g_gatel_serve (int) ; 
 int /*<<< orphan*/  memset (struct g_gate_ctl_create*,int /*<<< orphan*/ ,int) ; 
 int open (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  path ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 scalar_t__ sectorsize ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timeout ; 
 int unit ; 

__attribute__((used)) static void
g_gatel_create(void)
{
	struct g_gate_ctl_create ggioc;
	int fd;

	fd = open(path, g_gate_openflags(flags) | O_DIRECT | O_FSYNC);
	if (fd == -1)
		err(EXIT_FAILURE, "Cannot open %s", path);
	memset(&ggioc, 0, sizeof(ggioc));
	ggioc.gctl_version = G_GATE_VERSION;
	ggioc.gctl_unit = unit;
	ggioc.gctl_mediasize = g_gate_mediasize(fd);
	if (sectorsize == 0)
		sectorsize = g_gate_sectorsize(fd);
	ggioc.gctl_sectorsize = sectorsize;
	ggioc.gctl_timeout = timeout;
	ggioc.gctl_flags = flags;
	ggioc.gctl_maxcount = 0;
	strlcpy(ggioc.gctl_info, path, sizeof(ggioc.gctl_info));
	g_gate_ioctl(G_GATE_CMD_CREATE, &ggioc);
	if (unit == -1)
		printf("%s%u\n", G_GATE_PROVIDER_NAME, ggioc.gctl_unit);
	unit = ggioc.gctl_unit;
	g_gatel_serve(fd);
}