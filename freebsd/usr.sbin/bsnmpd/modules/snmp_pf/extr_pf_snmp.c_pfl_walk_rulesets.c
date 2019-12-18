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
struct pfioc_ruleset {char* path; scalar_t__ nr; char* name; } ;
typedef  int /*<<< orphan*/  prs ;
typedef  int /*<<< orphan*/  newpath ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETRULESET ; 
 int /*<<< orphan*/  DIOCGETRULESETS ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  PF_RESERVED_ANCHOR ; 
 int /*<<< orphan*/  bzero (struct pfioc_ruleset*,int) ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfioc_ruleset*) ; 
 scalar_t__ pfl_scan_ruleset (char const*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pfl_walk_rulesets(const char *path)
{
	struct pfioc_ruleset prs;
	char newpath[MAXPATHLEN];
	u_int32_t nr, i;

	if (pfl_scan_ruleset(path))
		goto err;

	bzero(&prs, sizeof(prs));
	strlcpy(prs.path, path, sizeof(prs.path));
	if (ioctl(dev, DIOCGETRULESETS, &prs)) {
		syslog(LOG_ERR, "pfl_walk_rulesets: ioctl(DIOCGETRULESETS): %s",
		    strerror(errno));
		goto err;
	}

	for (nr = prs.nr, i = 0; i < nr; i++) {
		prs.nr = i;
		if (ioctl(dev, DIOCGETRULESET, &prs)) {
			syslog(LOG_ERR, "pfl_walk_rulesets: ioctl(DIOCGETRULESET):"
			    " %s", strerror(errno));
			goto err;
		}

		if (strcmp(prs.name, PF_RESERVED_ANCHOR) == 0)
			continue;

		strlcpy(newpath, path, sizeof(newpath));
		if (path[0])
			strlcat(newpath, "/", sizeof(newpath));

		strlcat(newpath, prs.name, sizeof(newpath));
		if (pfl_walk_rulesets(newpath))
			goto err;
	}

	return (0);

err:
	return (-1);
}