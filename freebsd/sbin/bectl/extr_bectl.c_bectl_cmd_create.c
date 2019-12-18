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
typedef  int /*<<< orphan*/  snapshot ;

/* Variables and functions */
#define  BE_ERR_SUCCESS 128 
 int BE_MAXPATHLEN ; 
 int /*<<< orphan*/  be ; 
 char* be_active_path (int /*<<< orphan*/ ) ; 
 int be_create_depth (int /*<<< orphan*/ ,char*,char*,int) ; 
 int be_snapshot (int /*<<< orphan*/ ,char*,char*,int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int optopt ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int usage (int) ; 

__attribute__((used)) static int
bectl_cmd_create(int argc, char *argv[])
{
	char snapshot[BE_MAXPATHLEN];
	char *atpos, *bootenv, *snapname;
	int err, opt;
	bool recursive;

	snapname = NULL;
	recursive = false;
	while ((opt = getopt(argc, argv, "e:r")) != -1) {
		switch (opt) {
		case 'e':
			snapname = optarg;
			break;
		case 'r':
			recursive = true;
			break;
		default:
			fprintf(stderr, "bectl create: unknown option '-%c'\n",
			    optopt);
			return (usage(false));
		}
	}

	argc -= optind;
	argv += optind;

	if (argc != 1) {
		fprintf(stderr, "bectl create: wrong number of arguments\n");
		return (usage(false));
	}

	bootenv = *argv;

	err = BE_ERR_SUCCESS;
	if ((atpos = strchr(bootenv, '@')) != NULL) {
		/*
		 * This is the "create a snapshot variant". No new boot
		 * environment is to be created here.
		 */
		*atpos++ = '\0';
		err = be_snapshot(be, bootenv, atpos, recursive, NULL);
	} else {
		if (snapname == NULL)
			/* Create from currently booted BE */
			err = be_snapshot(be, be_active_path(be), NULL,
			    recursive, snapshot);
		else if (strchr(snapname, '@') != NULL)
			/* Create from given snapshot */
			strlcpy(snapshot, snapname, sizeof(snapshot));
		else
			/* Create from given BE */
			err = be_snapshot(be, snapname, NULL, recursive,
			    snapshot);

		if (err == BE_ERR_SUCCESS)
			err = be_create_depth(be, bootenv, snapshot,
					      recursive == true ? -1 : 0);
	}

	switch (err) {
	case BE_ERR_SUCCESS:
		break;
	default:
		if (atpos != NULL)
			fprintf(stderr,
			    "failed to create a snapshot '%s' of '%s'\n",
			    atpos, bootenv);
		else if (snapname == NULL)
			fprintf(stderr,
			    "failed to create bootenv %s\n", bootenv);
		else
			fprintf(stderr,
			    "failed to create bootenv %s from snapshot %s\n",
			    bootenv, snapname);
	}

	return (err);
}