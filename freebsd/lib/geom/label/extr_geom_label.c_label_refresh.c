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
struct gctl_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  g_close (int) ; 
 int g_open (char const*,int) ; 
 int /*<<< orphan*/  gctl_error (struct gctl_req*,char*) ; 
 char* gctl_get_ascii (struct gctl_req*,char*,int) ; 
 int gctl_get_int (struct gctl_req*,char*) ; 
 int /*<<< orphan*/  printf (char*,char const*,...) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
label_refresh(struct gctl_req *req)
{
	const char *name;
	int i, nargs, fd;

	nargs = gctl_get_int(req, "nargs");
	if (nargs < 1) {
		gctl_error(req, "Too few arguments.");
		return;
	}

	for (i = 0; i < nargs; i++) {
		name = gctl_get_ascii(req, "arg%d", i);
		fd = g_open(name, 1);
		if (fd == -1) {
			printf("Can't refresh metadata from %s: %s.\n",
			    name, strerror(errno));
		} else {
			printf("Metadata from %s refreshed.\n", name);
			(void)g_close(fd);
		}
	}
}