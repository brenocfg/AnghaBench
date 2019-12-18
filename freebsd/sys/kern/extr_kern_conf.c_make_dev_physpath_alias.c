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
struct cdev {char const* si_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int MAKEDEV_NOWAIT ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_WAITOK ; 
 int SPECNAMELEN ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  destroy_dev (struct cdev*) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int make_dev_alias_p (int,struct cdev**,struct cdev*,char*,char*) ; 
 char* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 

int
make_dev_physpath_alias(int flags, struct cdev **cdev, struct cdev *pdev, 
    struct cdev *old_alias, const char *physpath)
{
	char *devfspath;
	int physpath_len;
	int max_parentpath_len;
	int parentpath_len;
	int devfspathbuf_len;
	int mflags;
	int ret;

	*cdev = NULL;
	devfspath = NULL;
	physpath_len = strlen(physpath);
	ret = EINVAL;
	if (physpath_len == 0)
		goto out;

	if (strncmp("id1,", physpath, 4) == 0) {
		physpath += 4;
		physpath_len -= 4;
		if (physpath_len == 0)
			goto out;
	}

	max_parentpath_len = SPECNAMELEN - physpath_len - /*/*/1;
	parentpath_len = strlen(pdev->si_name);
	if (max_parentpath_len < parentpath_len) {
		if (bootverbose)
			printf("WARNING: Unable to alias %s "
			    "to %s/%s - path too long\n",
			    pdev->si_name, physpath, pdev->si_name);
		ret = ENAMETOOLONG;
		goto out;
	}

	mflags = (flags & MAKEDEV_NOWAIT) ? M_NOWAIT : M_WAITOK;
	devfspathbuf_len = physpath_len + /*/*/1 + parentpath_len + /*NUL*/1;
	devfspath = malloc(devfspathbuf_len, M_DEVBUF, mflags);
	if (devfspath == NULL) {
		ret = ENOMEM;
		goto out;
	}

	sprintf(devfspath, "%s/%s", physpath, pdev->si_name);
	if (old_alias != NULL && strcmp(old_alias->si_name, devfspath) == 0) {
		/* Retain the existing alias. */
		*cdev = old_alias;
		old_alias = NULL;
		ret = 0;
	} else {
		ret = make_dev_alias_p(flags, cdev, pdev, "%s", devfspath);
	}
out:
	if (old_alias != NULL)	
		destroy_dev(old_alias);
	if (devfspath != NULL)
		free(devfspath, M_DEVBUF);
	return (ret);
}