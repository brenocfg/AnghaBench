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
struct disk_devdesc {TYPE_1__ dd; } ;
struct devsw {char const* dv_name; int dv_type; } ;

/* Variables and functions */
#define  DEVT_CD 132 
#define  DEVT_DISK 131 
#define  DEVT_NET 130 
#define  DEVT_NONE 129 
#define  DEVT_ZFS 128 
 int EINVAL ; 
 int ENOENT ; 
 int EUNIT ; 
 struct devsw** devsw ; 
 int disk_parsedev (struct disk_devdesc*,char const*,char const**) ; 
 int /*<<< orphan*/  free (struct disk_devdesc*) ; 
 struct disk_devdesc* malloc (int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 
 int zfs_parsedev (struct zfs_devdesc*,char const*,char const**) ; 

__attribute__((used)) static int
userboot_parsedev(struct disk_devdesc **dev, const char *devspec, const char **path)
{
    struct disk_devdesc *idev;
    struct devsw	*dv;
    int			i, unit, err;
    const char		*cp;
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
    idev = malloc(sizeof(struct disk_devdesc));
    err = 0;
    np = (devspec + strlen(dv->dv_name));
        
    switch(dv->dv_type) {
    case DEVT_NONE:			/* XXX what to do here?  Do we care? */
	break;

    case DEVT_DISK:
	err = disk_parsedev(idev, np, path);
	if (err != 0)
	    goto fail;
	break;

    case DEVT_CD:
    case DEVT_NET:
	unit = 0;

	if (*np && (*np != ':')) {
	    unit = strtol(np, (char **)&cp, 0);	/* get unit number if present */
	    if (cp == np) {
		err = EUNIT;
		goto fail;
	    }
	} else {
		cp = np;
	}
	if (*cp && (*cp != ':')) {
	    err = EINVAL;
	    goto fail;
	}

	idev->dd.d_unit = unit;
	if (path != NULL)
	    *path = (*cp == 0) ? cp : cp + 1;
	break;

    case DEVT_ZFS:
#if defined(USERBOOT_ZFS_SUPPORT)
	    err = zfs_parsedev((struct zfs_devdesc *)idev, np, path);
	    if (err != 0)
		    goto fail;
	    break;
#else
	    /* FALLTHROUGH */
#endif

    default:
	err = EINVAL;
	goto fail;
    }
    idev->dd.d_dev = dv;
    if (dev == NULL) {
	free(idev);
    } else {
	*dev = idev;
    }
    return(0);

 fail:
    free(idev);
    return(err);
}