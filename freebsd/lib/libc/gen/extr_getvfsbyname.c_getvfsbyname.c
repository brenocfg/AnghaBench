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
struct xvfsconf {int /*<<< orphan*/  vfc_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 scalar_t__ are_fusefs (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (struct xvfsconf*) ; 
 struct xvfsconf* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (struct xvfsconf*,struct xvfsconf*,int) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctlbyname (char*,struct xvfsconf*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
getvfsbyname(const char *fsname, struct xvfsconf *vfcp)
{
	struct xvfsconf *xvfsp;
	size_t buflen;
	int cnt, i;

	if (sysctlbyname("vfs.conflist", NULL, &buflen, NULL, 0) < 0)
		return (-1);
	xvfsp = malloc(buflen);
	if (xvfsp == NULL)
		return (-1);
	if (sysctlbyname("vfs.conflist", xvfsp, &buflen, NULL, 0) < 0) {
		free(xvfsp);
		return (-1);
	}
	cnt = buflen / sizeof(struct xvfsconf);
	for (i = 0; i < cnt; i++) {
		if (strcmp(fsname, xvfsp[i].vfc_name) == 0 ||
		    are_fusefs(fsname, xvfsp[i].vfc_name)) {
			memcpy(vfcp, xvfsp + i, sizeof(struct xvfsconf));
			free(xvfsp);
			return (0);
		}
	}
	free(xvfsp);
	errno = ENOENT;
	return (-1);
}