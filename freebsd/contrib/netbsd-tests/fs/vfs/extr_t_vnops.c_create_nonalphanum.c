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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int O_RDWR ; 
 int /*<<< orphan*/  RL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RLF (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rump_sys_chdir (char const*) ; 
 int /*<<< orphan*/  rump_sys_close (int) ; 
 int rump_sys_open (char*,int,int) ; 
 int /*<<< orphan*/  rump_sys_unlink (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static void
create_nonalphanum(const atf_tc_t *tc, const char *mp)
{
	char buf[64];
	int i;

	RL(rump_sys_chdir(mp));

	for (i = 0; i < 256; i++) {
		int fd;
		snprintf(buf, sizeof(buf), "%c", i);
		fd = rump_sys_open(buf, O_RDWR|O_CREAT|O_EXCL, 0666);
		if (fd == -1)
			continue;
		RLF(rump_sys_close(fd), "%d", fd);
		RLF(rump_sys_unlink(buf), "%s", buf);
	}
	printf("\n");

	rump_sys_chdir("/");
}