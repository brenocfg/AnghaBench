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
struct TYPE_3__ {int /*<<< orphan*/  block_size; int /*<<< orphan*/  block_count; } ;
struct device_info {int type; TYPE_1__ di_stor; } ;
struct TYPE_4__ {int handle; int type; int /*<<< orphan*/  bsize; int /*<<< orphan*/  blocks; scalar_t__ opened; } ;

/* Variables and functions */
 int DEV_TYP_STOR ; 
 int UB_MAX_DEV ; 
 int /*<<< orphan*/  debugf (char*,...) ; 
 int devs_no ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_2__* stor_info ; 
 int stor_info_no ; 
 struct device_info* ub_dev_get (int) ; 

__attribute__((used)) static int
stor_init(void)
{
	struct device_info *di;
	int i;

	if (devs_no == 0) {
		printf("No U-Boot devices! Really enumerated?\n");
		return (-1);
	}

	for (i = 0; i < devs_no; i++) {
		di = ub_dev_get(i);
		if ((di != NULL) && (di->type & DEV_TYP_STOR)) {
			if (stor_info_no >= UB_MAX_DEV) {
				printf("Too many storage devices: %d\n",
				    stor_info_no);
				return (-1);
			}
			stor_info[stor_info_no].handle = i;
			stor_info[stor_info_no].opened = 0;
			stor_info[stor_info_no].type = di->type;
			stor_info[stor_info_no].blocks =
			    di->di_stor.block_count;
			stor_info[stor_info_no].bsize =
			    di->di_stor.block_size;
			stor_info_no++;
		}
	}

	if (!stor_info_no) {
		debugf("No storage devices\n");
		return (-1);
	}

	debugf("storage devices found: %d\n", stor_info_no);
	return (0);
}