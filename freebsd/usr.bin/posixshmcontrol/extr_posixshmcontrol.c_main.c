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
struct opmode {int (* impl ) (int,char**) ;int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ nitems (struct opmode*) ; 
 struct opmode* opmodes ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int stub1 (int,char**) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	const struct opmode *opmode;
	int i, ret;

	ret = 0;
	opmode = NULL;

	if (argc < 2) {
		usage();
		exit(2);
	}
	for (i = 0; i < (int)nitems(opmodes); i++) {
		if (strcmp(argv[1], opmodes[i].cmd) == 0) {
			opmode = &opmodes[i];
			break;
		}
	}
	if (opmode == NULL) {
		usage();
		exit(2);
	}
	ret = opmode->impl(argc - 1, argv + 1);
	exit(ret);
}