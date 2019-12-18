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
#define  BE_ERR_SUCCESS 128 
 int BE_MAXPATHLEN ; 
 int BE_MNT_DEEP ; 
 int /*<<< orphan*/  be ; 
 int be_mount (int /*<<< orphan*/ ,char*,char*,int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int usage (int) ; 

__attribute__((used)) static int
bectl_cmd_mount(int argc, char *argv[])
{
	char result_loc[BE_MAXPATHLEN];
	char *bootenv, *mountpoint;
	int err, mntflags;

	/* XXX TODO: Allow shallow */
	mntflags = BE_MNT_DEEP;
	if (argc < 2) {
		fprintf(stderr, "bectl mount: missing argument(s)\n");
		return (usage(false));
	}

	if (argc > 3) {
		fprintf(stderr, "bectl mount: too many arguments\n");
		return (usage(false));
	}

	bootenv = argv[1];
	mountpoint = ((argc == 3) ? argv[2] : NULL);

	err = be_mount(be, bootenv, mountpoint, mntflags, result_loc);

	switch (err) {
	case BE_ERR_SUCCESS:
		printf("successfully mounted %s at %s\n", bootenv, result_loc);
		break;
	default:
		fprintf(stderr,
		    (argc == 3) ? "failed to mount bootenv %s at %s\n" :
		    "failed to mount bootenv %s at temporary path %s\n",
		    bootenv, mountpoint);
	}

	return (err);
}