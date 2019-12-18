#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  type ;
struct zfs_devdesc {int dummy; } ;
struct TYPE_2__ {struct devsw* d_dev; } ;
struct ofw_devdesc {TYPE_1__ dd; int /*<<< orphan*/  d_path; } ;
struct devsw {scalar_t__ dv_type; int /*<<< orphan*/  dv_name; } ;
typedef  int phandle_t ;

/* Variables and functions */
 scalar_t__ DEVT_ZFS ; 
 int ENOENT ; 
 int ENOMEM ; 
 int OF_finddevice (char*) ; 
 int OF_getprop (int,char*,char*,int) ; 
 int /*<<< orphan*/  bcopy (char const*,char*,int) ; 
 struct devsw** devsw ; 
 int /*<<< orphan*/  free (struct ofw_devdesc*) ; 
 struct ofw_devdesc* malloc (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int zfs_parsedev (struct zfs_devdesc*,char const*,char const**) ; 

__attribute__((used)) static int
ofw_parsedev(struct ofw_devdesc **dev, const char *devspec, const char **path)
{
    struct ofw_devdesc	*idev;
    struct devsw	*dv;
    phandle_t		handle;
    const char		*p;
    const char		*s;
    char		*ep;
    char		name[256];
    char		type[64];
    int			err;
    int			len;
    int			i;

    for (p = s = devspec; *s != '\0'; p = s) {
	if ((s = strchr(p + 1, '/')) == NULL)
	    s = strchr(p, '\0');
	len = s - devspec;
	bcopy(devspec, name, len);
	name[len] = '\0';
	if ((handle = OF_finddevice(name)) == -1) {
	    bcopy(name, type, len);
	    type[len] = '\0';
	} else if (OF_getprop(handle, "device_type", type, sizeof(type)) == -1)
	    continue;
	for (i = 0; (dv = devsw[i]) != NULL; i++) {
	    if (strncmp(dv->dv_name, type, strlen(dv->dv_name)) == 0)
		goto found;
	}
    }
    return(ENOENT);

found:
    if (path != NULL)
	*path = s;
    idev = malloc(sizeof(struct ofw_devdesc));
    if (idev == NULL) {
	printf("ofw_parsedev: malloc failed\n");
	return ENOMEM;
    }
    strcpy(idev->d_path, name);
    idev->dd.d_dev = dv;
    if (dv->dv_type == DEVT_ZFS) {
	p = devspec + strlen(dv->dv_name);
	err = zfs_parsedev((struct zfs_devdesc *)idev, p, path);
	if (err != 0) {
	    free(idev);
	    return (err);
	}
    }

    if (dev == NULL) {
	free(idev);
    } else {
	*dev = idev;
    }
    return(0);
}