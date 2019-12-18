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
 int /*<<< orphan*/  disk ; 
 int dumpfreespace (char const*,int) ; 
 int dumpfs (char const*) ; 
 int dumpfsid () ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int marshal (char const*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  ufs_disk_close (int /*<<< orphan*/ *) ; 
 int ufs_disk_fillout (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  ufserr (char const*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	const char *name;
	int ch, dofreespace, domarshal, dolabel, eval;

	dofreespace = domarshal = dolabel = eval = 0;

	while ((ch = getopt(argc, argv, "lfm")) != -1) {
		switch (ch) {
		case 'f':
			dofreespace++;
			break;
		case 'm':
			domarshal = 1;
			break;
		case 'l':
			dolabel = 1;
			break;
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc < 1)
		usage();
	if (dofreespace && domarshal)
		usage();
	if (dofreespace > 2)
		usage();

	while ((name = *argv++) != NULL) {
		if (ufs_disk_fillout(&disk, name) == -1) {
			ufserr(name);
			eval |= 1;
			continue;
		}
		if (dofreespace)
			eval |= dumpfreespace(name, dofreespace);
		else if (domarshal)
			eval |= marshal(name);
		else if (dolabel)
			eval |= dumpfsid();
		else
			eval |= dumpfs(name);
		ufs_disk_close(&disk);
	}
	exit(eval);
}