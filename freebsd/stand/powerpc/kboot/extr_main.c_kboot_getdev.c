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
struct devsw {int /*<<< orphan*/  dv_name; } ;
struct devdesc {int /*<<< orphan*/  d_opendata; scalar_t__ d_unit; struct devsw* d_dev; } ;

/* Variables and functions */
 int ENOENT ; 
 struct devsw** devsw ; 
 char* getenv (char*) ; 
 struct devdesc* malloc (int) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

int
kboot_getdev(void **vdev, const char *devspec, const char **path)
{
	int i;
	const char *devpath, *filepath;
	struct devsw *dv;
	struct devdesc *desc;

	if (strchr(devspec, ':') != NULL) {
		devpath = devspec;
		filepath = strchr(devspec, ':') + 1;
	} else {
		devpath = getenv("currdev");
		filepath = devspec;
	}

	for (i = 0; (dv = devsw[i]) != NULL; i++) {
		if (strncmp(dv->dv_name, devpath, strlen(dv->dv_name)) == 0)
			goto found;
	}
	return (ENOENT);

found:
	if (path != NULL && filepath != NULL)
		*path = filepath;
	else if (path != NULL)
		*path = strchr(devspec, ':') + 1;

	if (vdev != NULL) {
		desc = malloc(sizeof(*desc));
		desc->d_dev = dv;
		desc->d_unit = 0;
		desc->d_opendata = strdup(devpath);
		*vdev = desc;
	}

	return (0);
}