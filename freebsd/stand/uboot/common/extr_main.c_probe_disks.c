#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct open_file {TYPE_3__* f_devdata; } ;
struct TYPE_11__ {int (* dv_open ) (struct open_file*,TYPE_3__*) ;} ;
struct TYPE_9__ {int d_unit; } ;
struct TYPE_8__ {int d_slice; int d_partition; } ;
struct TYPE_10__ {TYPE_2__ dd; TYPE_1__ d_disk; } ;

/* Variables and functions */
 int UB_MAX_DEV ; 
 TYPE_3__ currdev ; 
 char* device_typename (int) ; 
 TYPE_6__** devsw ; 
 int /*<<< orphan*/  print_disk_probe_info () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int stub1 (struct open_file*,TYPE_3__*) ; 
 int stub2 (struct open_file*,TYPE_3__*) ; 
 int stub3 (struct open_file*,TYPE_3__*) ; 
 void* uboot_diskgetunit (int,int) ; 

__attribute__((used)) static int
probe_disks(int devidx, int load_type, int load_unit, int load_slice, 
    int load_partition)
{
	int open_result, unit;
	struct open_file f;

	currdev.d_disk.d_slice = load_slice;
	currdev.d_disk.d_partition = load_partition;

	f.f_devdata = &currdev;
	open_result = -1;

	if (load_type == -1) {
		printf("  Probing all disk devices...\n");
		/* Try each disk in succession until one works.  */
		for (currdev.dd.d_unit = 0; currdev.dd.d_unit < UB_MAX_DEV;
		     currdev.dd.d_unit++) {
			print_disk_probe_info();
			open_result = devsw[devidx]->dv_open(&f, &currdev);
			if (open_result == 0) {
				printf(" good.\n");
				return (0);
			}
			printf("\n");
		}
		return (-1);
	}

	if (load_unit == -1) {
		printf("  Probing all %s devices...\n", device_typename(load_type));
		/* Try each disk of given type in succession until one works. */
		for (unit = 0; unit < UB_MAX_DEV; unit++) {
			currdev.dd.d_unit = uboot_diskgetunit(load_type, unit);
			if (currdev.dd.d_unit == -1)
				break;
			print_disk_probe_info();
			open_result = devsw[devidx]->dv_open(&f, &currdev);
			if (open_result == 0) {
				printf(" good.\n");
				return (0);
			}
			printf("\n");
		}
		return (-1);
	}

	if ((currdev.dd.d_unit = uboot_diskgetunit(load_type, load_unit)) != -1) {
		print_disk_probe_info();
		open_result = devsw[devidx]->dv_open(&f,&currdev);
		if (open_result == 0) {
			printf(" good.\n");
			return (0);
		}
		printf("\n");
	}

	printf("  Requested disk type/unit/slice/partition not found\n");
	return (-1);
}