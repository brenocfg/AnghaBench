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
struct hd_geometry {int /*<<< orphan*/  cylinders; int /*<<< orphan*/  sectors; int /*<<< orphan*/  heads; } ;
struct floppy_struct {int /*<<< orphan*/  track; int /*<<< orphan*/  sect; int /*<<< orphan*/  head; } ;
struct block_device {TYPE_1__* bd_disk; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd_device; } ;
struct TYPE_3__ {scalar_t__ private_data; } ;

/* Variables and functions */
 int ITYPE (int /*<<< orphan*/ ) ; 
 TYPE_2__* drive_state ; 
 int get_floppy_geometry (int,int,struct floppy_struct**) ; 

__attribute__((used)) static int fd_getgeo(struct block_device *bdev, struct hd_geometry *geo)
{
	int drive = (long)bdev->bd_disk->private_data;
	int type = ITYPE(drive_state[drive].fd_device);
	struct floppy_struct *g;
	int ret;

	ret = get_floppy_geometry(drive, type, &g);
	if (ret)
		return ret;

	geo->heads = g->head;
	geo->sectors = g->sect;
	geo->cylinders = g->track;
	return 0;
}