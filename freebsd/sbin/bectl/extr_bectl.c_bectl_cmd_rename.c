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
 int /*<<< orphan*/  be ; 
 int be_rename (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 int usage (int) ; 

__attribute__((used)) static int
bectl_cmd_rename(int argc, char *argv[])
{
	char *dest, *src;
	int err;

	if (argc < 3) {
		fprintf(stderr, "bectl rename: missing argument\n");
		return (usage(false));
	}

	if (argc > 3) {
		fprintf(stderr, "bectl rename: too many arguments\n");
		return (usage(false));
	}

	src = argv[1];
	dest = argv[2];

	err = be_rename(be, src, dest);

	switch (err) {
	case BE_ERR_SUCCESS:
		break;
	default:
		fprintf(stderr, "failed to rename bootenv %s to %s\n",
		    src, dest);
	}

	return (0);
}