#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* d_dev; int /*<<< orphan*/  d_unit; } ;
struct i386_devdesc {TYPE_2__ dd; } ;
struct TYPE_3__ {int dv_type; char* dv_name; } ;

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
i386_fmtdev(void *vdev)
{
    struct i386_devdesc	*dev = (struct i386_devdesc *)vdev;
    static char		buf[128];	/* XXX device length constant? */

    switch(dev->dd.d_dev->dv_type) {
    case DEVT_NONE:
	strcpy(buf, "(no device)");
	break;

    case DEVT_CD:
    case DEVT_NET:
	sprintf(buf, "%s%d:", dev->dd.d_dev->dv_name, dev->dd.d_unit);
	break;

    case DEVT_DISK:
	return (disk_fmtdev(vdev));

    case DEVT_ZFS:
	return(zfs_fmtdev(vdev));
    }
    return(buf);
}