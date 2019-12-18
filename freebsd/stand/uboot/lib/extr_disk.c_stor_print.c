#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int d_unit; TYPE_2__* d_dev; } ;
struct disk_devdesc {int /*<<< orphan*/  d_partition; int /*<<< orphan*/  d_slice; TYPE_1__ dd; } ;
typedef  int /*<<< orphan*/  line ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct TYPE_5__ {char* dv_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PARTNONE ; 
 int /*<<< orphan*/  D_SLICENONE ; 
 TYPE_3__ SI (struct disk_devdesc*) ; 
 int /*<<< orphan*/  disk_close (struct disk_devdesc*) ; 
 int disk_print (struct disk_devdesc*,char*,int) ; 
 int pager_output (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int stor_info_no ; 
 scalar_t__ stor_opendev (struct disk_devdesc*) ; 
 char* ub_stor_type (int /*<<< orphan*/ ) ; 
 TYPE_2__ uboot_storage ; 

__attribute__((used)) static int
stor_print(int verbose)
{
	struct disk_devdesc dev;
	static char line[80];
	int i, ret = 0;

	if (stor_info_no == 0)
		return (ret);

	printf("%s devices:", uboot_storage.dv_name);
	if ((ret = pager_output("\n")) != 0)
		return (ret);

	for (i = 0; i < stor_info_no; i++) {
		dev.dd.d_dev = &uboot_storage;
		dev.dd.d_unit = i;
		dev.d_slice = D_SLICENONE;
		dev.d_partition = D_PARTNONE;
		snprintf(line, sizeof(line), "\tdisk%d (%s)\n", i,
		    ub_stor_type(SI(&dev).type));
		if ((ret = pager_output(line)) != 0)
			break;
		if (stor_opendev(&dev) == 0) {
			sprintf(line, "\tdisk%d", i);
			ret = disk_print(&dev, line, verbose);
			disk_close(&dev);
			if (ret != 0)
				break;
		}
	}
	return (ret);
}