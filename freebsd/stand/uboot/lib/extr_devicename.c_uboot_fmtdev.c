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
struct uboot_devdesc {TYPE_2__ dd; } ;
struct TYPE_3__ {int dv_type; char* dv_name; } ;

/* Variables and functions */
#define  DEVT_DISK 130 
#define  DEVT_NET 129 
#define  DEVT_NONE 128 
 char* disk_fmtdev (void*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

char *
uboot_fmtdev(void *vdev)
{
	struct uboot_devdesc *dev = (struct uboot_devdesc *)vdev;
	static char buf[128];

	switch(dev->dd.d_dev->dv_type) {
	case DEVT_NONE:
		strcpy(buf, "(no device)");
		break;

	case DEVT_DISK:
#ifdef LOADER_DISK_SUPPORT
		return (disk_fmtdev(vdev));
#endif

	case DEVT_NET:
		sprintf(buf, "%s%d:", dev->dd.d_dev->dv_name, dev->dd.d_unit);
		break;
	}
	return(buf);
}