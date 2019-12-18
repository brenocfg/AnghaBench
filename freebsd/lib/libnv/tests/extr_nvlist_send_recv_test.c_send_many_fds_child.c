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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int NFDS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int nopenfds () ; 
 int /*<<< orphan*/  nvlist_add_descriptor (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * nvlist_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_send (int,int /*<<< orphan*/ *) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
send_many_fds_child(int sock)
{
	char name[16];
	nvlist_t *nvl;
	int anfds, bnfds, fd, i, j;

	fd = open(_PATH_DEVNULL, O_RDONLY);
	ATF_REQUIRE(fd >= 0);

	for (i = 1; i < NFDS; i++) {
		nvl = nvlist_create(0);
		bnfds = nopenfds();
		if (bnfds == -1)
			err(EXIT_FAILURE, "sysctl");

		for (j = 0; j < i; j++) {
			snprintf(name, sizeof(name), "fd%d", j);
			nvlist_add_descriptor(nvl, name, fd);
		}
		nvlist_send(sock, nvl);
		nvlist_destroy(nvl);

		anfds = nopenfds();
		if (anfds == -1)
			err(EXIT_FAILURE, "sysctl");
		if (anfds != bnfds)
			errx(EXIT_FAILURE, "fd count mismatch");
	}
}