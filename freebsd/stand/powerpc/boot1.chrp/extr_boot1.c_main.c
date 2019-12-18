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
 char* PATH_LOADER ; 
 scalar_t__ bootdev ; 
 char* bootpath ; 
 int /*<<< orphan*/  chosenh ; 
 scalar_t__ domount (char*,int) ; 
 int /*<<< orphan*/  load (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  ofw_close (scalar_t__) ; 
 int /*<<< orphan*/  ofw_setprop (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int ac, char **av)
{
	const char *path;
	char bootpath_full[255];
	int i, len;

	path = PATH_LOADER;
	for (i = 0; i < ac; i++) {
		switch (av[i][0]) {
		case '-':
			switch (av[i][1]) {
			default:
				usage();
			}
			break;
		default:
			path = av[i];
			break;
		}
	}

	printf(" \n>> FreeBSD/powerpc Open Firmware boot block\n"
	"   Boot path:   %s\n"
	"   Boot loader: %s\n", bootpath, path);

	len = 0;
	while (bootpath[len] != '\0') len++;

	memcpy(bootpath_full,bootpath,len+1);

	if (bootpath_full[len-1] != ':') {
		/* First try full volume */
		if (domount(bootpath_full,1) == 0)
			goto out;

		/* Add a : so that we try partitions if that fails */
		if (bootdev > 0)
			ofw_close(bootdev);
		bootpath_full[len] = ':';
		len += 1;
	}

	/* Loop through first 16 partitions to find a UFS one */
	for (i = 0; i < 16; i++) {
		if (i < 10) {
			bootpath_full[len] = i + '0';
			bootpath_full[len+1] = '\0';
		} else {
			bootpath_full[len] = '1';
			bootpath_full[len+1] = i - 10 + '0';
			bootpath_full[len+2] = '\0';
		}
			
		if (domount(bootpath_full,1) >= 0)
			break;

		if (bootdev > 0)
			ofw_close(bootdev);
	}

	if (i >= 16)
		panic("domount");

out:
	printf("   Boot volume:   %s\n",bootpath_full);
	ofw_setprop(chosenh, "bootargs", bootpath_full, len+2);
	load(path);
	return (1);
}