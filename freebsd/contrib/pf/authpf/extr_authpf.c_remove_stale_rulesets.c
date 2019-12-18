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
struct pfioc_ruleset {char* name; scalar_t__ nr; int /*<<< orphan*/  path; } ;
typedef  int /*<<< orphan*/  prs ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGETRULESET ; 
 int /*<<< orphan*/  DIOCGETRULESETS ; 
 scalar_t__ EINVAL ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  anchorname ; 
 int /*<<< orphan*/  dev ; 
 scalar_t__ errno ; 
 scalar_t__ getpid () ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pfioc_ruleset*) ; 
 scalar_t__ kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct pfioc_ruleset*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ recursive_ruleset_purge (int /*<<< orphan*/ ,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strtoul (char*,char**,int) ; 

__attribute__((used)) static int
remove_stale_rulesets(void)
{
	struct pfioc_ruleset	 prs;
	u_int32_t		 nr;

	memset(&prs, 0, sizeof(prs));
	strlcpy(prs.path, anchorname, sizeof(prs.path));
	if (ioctl(dev, DIOCGETRULESETS, &prs)) {
		if (errno == EINVAL)
			return (0);
		else
			return (1);
	}

	nr = prs.nr;
	while (nr) {
		char	*s, *t;
		pid_t	 pid;

		prs.nr = nr - 1;
		if (ioctl(dev, DIOCGETRULESET, &prs))
			return (1);
		errno = 0;
		if ((t = strchr(prs.name, '(')) == NULL)
			t = prs.name;
		else
			t++;
		pid = strtoul(t, &s, 10);
		if (!prs.name[0] || errno ||
		    (*s && (t == prs.name || *s != ')')))
			return (1);
		if ((kill(pid, 0) && errno != EPERM) || pid == getpid()) {
			if (recursive_ruleset_purge(anchorname, prs.name))
				return (1);
		}
		nr--;
	}
	return (0);
}