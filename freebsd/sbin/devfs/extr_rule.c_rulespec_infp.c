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
struct devfs_rule {int dummy; } ;
typedef  int /*<<< orphan*/  devfs_rsnum ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ efgetln (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ioctl (int /*<<< orphan*/ ,unsigned long,struct devfs_rule*) ; 
 int /*<<< orphan*/  mpfd ; 
 int /*<<< orphan*/  rulespec_instr (struct devfs_rule*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stdin ; 

__attribute__((used)) static void
rulespec_infp(FILE *fp, unsigned long request, devfs_rsnum rsnum)
{
	struct devfs_rule dr;
	char *line;
	int rv;

	assert(fp == stdin);	/* XXX: De-hardcode "stdin" from error msg. */
	while (efgetln(fp, &line)) {
		rulespec_instr(&dr, line, rsnum);
		rv = ioctl(mpfd, request, &dr);
		if (rv == -1)
			err(1, "ioctl");
		free(line);	/* efgetln() always malloc()s. */
	}
	if (ferror(stdin))
		err(1, "stdin");
}