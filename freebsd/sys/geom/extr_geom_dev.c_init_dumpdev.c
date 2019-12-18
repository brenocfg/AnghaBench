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
struct g_consumer {int dummy; } ;
struct diocskerneldump_arg {int /*<<< orphan*/  kda_index; } ;
struct cdev {scalar_t__ si_drv2; } ;
typedef  int /*<<< orphan*/  kda ;

/* Variables and functions */
 int /*<<< orphan*/  KDA_APPEND ; 
 int /*<<< orphan*/  bzero (struct diocskerneldump_arg*,int) ; 
 char* devtoname (struct cdev*) ; 
 int /*<<< orphan*/ * dumpdev ; 
 int /*<<< orphan*/  freeenv (int /*<<< orphan*/ *) ; 
 int g_access (struct g_consumer*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int g_dev_setdumpdev (struct cdev*,struct diocskerneldump_arg*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char const*,size_t) ; 

__attribute__((used)) static int
init_dumpdev(struct cdev *dev)
{
	struct diocskerneldump_arg kda;
	struct g_consumer *cp;
	const char *devprefix = "/dev/", *devname;
	int error;
	size_t len;

	bzero(&kda, sizeof(kda));
	kda.kda_index = KDA_APPEND;

	if (dumpdev == NULL)
		return (0);

	len = strlen(devprefix);
	devname = devtoname(dev);
	if (strcmp(devname, dumpdev) != 0 &&
	   (strncmp(dumpdev, devprefix, len) != 0 ||
	    strcmp(devname, dumpdev + len) != 0))
		return (0);

	cp = (struct g_consumer *)dev->si_drv2;
	error = g_access(cp, 1, 0, 0);
	if (error != 0)
		return (error);

	error = g_dev_setdumpdev(dev, &kda);
	if (error == 0) {
		freeenv(dumpdev);
		dumpdev = NULL;
	}

	(void)g_access(cp, -1, 0, 0);

	return (error);
}