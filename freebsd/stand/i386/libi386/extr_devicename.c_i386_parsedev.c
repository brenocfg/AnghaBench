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
struct zfs_devdesc {int dummy; } ;
struct TYPE_2__ {int d_unit; struct devsw* d_dev; } ;
struct i386_devdesc {TYPE_1__ dd; } ;
struct disk_devdesc {int dummy; } ;
struct devsw {char const* dv_name; int dv_type; } ;
struct devdesc {int dummy; } ;

/* Variables and functions */
#define  DEVT_DISK 130 
#define  DEVT_NONE 129 
#define  DEVT_ZFS 128 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int EUNIT ; 
 struct devsw** devsw ; 
 int disk_parsedev (struct disk_devdesc*,char const*,char const**) ; 
 int /*<<< orphan*/  free (struct i386_devdesc*) ; 
 struct i386_devdesc* malloc (int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 
 int zfs_parsedev (struct zfs_devdesc*,char const*,char const**) ; 

__attribute__((used)) static int
i386_parsedev(struct i386_devdesc **dev, const char *devspec, const char **path)
{
    struct i386_devdesc *idev;
    struct devsw	*dv;
    int			i, unit, err;
    char		*cp;
    const char		*np;

    /* minimum length check */
    if (strlen(devspec) < 2)
	return(EINVAL);

    /* look for a device that matches */
    for (i = 0, dv = NULL; devsw[i] != NULL; i++) {
	if (!strncmp(devspec, devsw[i]->dv_name, strlen(devsw[i]->dv_name))) {
	    dv = devsw[i];
	    break;
	}
    }
    if (dv == NULL)
	return(ENOENT);

    np = (devspec + strlen(dv->dv_name));
    idev = NULL;
    err = 0;
        
    switch(dv->dv_type) {
    case DEVT_NONE:
	break;

    case DEVT_DISK:
	idev = malloc(sizeof(struct i386_devdesc));
	if (idev == NULL)
	    return (ENOMEM);

	err = disk_parsedev((struct disk_devdesc *)idev, np, path);
	if (err != 0)
	    goto fail;
	break;

    case DEVT_ZFS:
	idev = malloc(sizeof (struct zfs_devdesc));
	if (idev == NULL)
	    return (ENOMEM);

	err = zfs_parsedev((struct zfs_devdesc *)idev, np, path);
	if (err != 0)
	    goto fail;
	break;

    default:
	idev = malloc(sizeof (struct devdesc));
	if (idev == NULL)
	    return (ENOMEM);

	unit = 0;
	cp = (char *)np;

	if (*np && (*np != ':')) {
	    unit = strtol(np, &cp, 0);	/* get unit number if present */
	    if (cp == np) {
		err = EUNIT;
		goto fail;
	    }
	}

	if (*cp && (*cp != ':')) {
	    err = EINVAL;
	    goto fail;
	}

	idev->dd.d_unit = unit;
	if (path != NULL)
	    *path = (*cp == 0) ? cp : cp + 1;
	break;
    }
    idev->dd.d_dev = dv;
    if (dev != NULL)
	*dev = idev;
    else
	free(idev);

    return(0);

 fail:
    free(idev);
    return(err);
}