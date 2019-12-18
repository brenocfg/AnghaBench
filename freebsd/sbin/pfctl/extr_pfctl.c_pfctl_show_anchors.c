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
typedef  scalar_t__ u_int32_t ;
typedef  int /*<<< orphan*/  sub ;
struct pfioc_ruleset {char* path; scalar_t__ nr; char* name; } ;
typedef  int /*<<< orphan*/  pr ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETRULESET ; 
 int /*<<< orphan*/  DIOCGETRULESETS ; 
 scalar_t__ EINVAL ; 
 int MAXPATHLEN ; 
 int PF_OPT_VERBOSE ; 
 int /*<<< orphan*/  PF_RESERVED_ANCHOR ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct pfioc_ruleset*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (struct pfioc_ruleset*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 

int
pfctl_show_anchors(int dev, int opts, char *anchorname)
{
	struct pfioc_ruleset	 pr;
	u_int32_t		 mnr, nr;

	memset(&pr, 0, sizeof(pr));
	memcpy(pr.path, anchorname, sizeof(pr.path));
	if (ioctl(dev, DIOCGETRULESETS, &pr)) {
		if (errno == EINVAL)
			fprintf(stderr, "Anchor '%s' not found.\n",
			    anchorname);
		else
			err(1, "DIOCGETRULESETS");
		return (-1);
	}
	mnr = pr.nr;
	for (nr = 0; nr < mnr; ++nr) {
		char sub[MAXPATHLEN];

		pr.nr = nr;
		if (ioctl(dev, DIOCGETRULESET, &pr))
			err(1, "DIOCGETRULESET");
		if (!strcmp(pr.name, PF_RESERVED_ANCHOR))
			continue;
		sub[0] = 0;
		if (pr.path[0]) {
			strlcat(sub, pr.path, sizeof(sub));
			strlcat(sub, "/", sizeof(sub));
		}
		strlcat(sub, pr.name, sizeof(sub));
		if (sub[0] != '_' || (opts & PF_OPT_VERBOSE))
			printf("  %s\n", sub);
		if ((opts & PF_OPT_VERBOSE) && pfctl_show_anchors(dev, opts, sub))
			return (-1);
	}
	return (0);
}