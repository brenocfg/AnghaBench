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
struct devdesc {TYPE_1__* d_dev; int /*<<< orphan*/  d_unit; } ;
struct TYPE_2__ {int dv_type; char* dv_name; } ;

/* Variables and functions */
#define  DEVT_CD 132 
#define  DEVT_DISK 131 
#define  DEVT_NET 130 
#define  DEVT_NONE 129 
#define  DEVT_ZFS 128 
 char* disk_fmtdev (void*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 char* zfs_fmtdev (void*) ; 

char *
userboot_fmtdev(void *vdev)
{
    struct devdesc	*dev = (struct devdesc *)vdev;
    static char		buf[128];	/* XXX device length constant? */

    switch(dev->d_dev->dv_type) {
    case DEVT_NONE:
	strcpy(buf, "(no device)");
	break;

    case DEVT_CD:
	sprintf(buf, "%s%d:", dev->d_dev->dv_name, dev->d_unit);
	break;

    case DEVT_DISK:
	return (disk_fmtdev(vdev));

    case DEVT_NET:
	sprintf(buf, "%s%d:", dev->d_dev->dv_name, dev->d_unit);
	break;

    case DEVT_ZFS:
#if defined(USERBOOT_ZFS_SUPPORT)
	return (zfs_fmtdev(vdev));
#else
	sprintf(buf, "%s%d:", dev->d_dev->dv_name, dev->d_unit);
#endif
	break;
    }
    return(buf);
}