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
struct TYPE_3__ {int flags; int number; int channel; int device; int /*<<< orphan*/  id; } ;
struct promise_raid_conf {char* promise_id; int disk_offset; int disk_sectors; int disk_rebuild; int generation; int status; int type; int total_disks; int stripe_shift; int array_width; int array_number; int total_sectors; int cylinders; int heads; int sectors; char* name; int magic_3; int magic_4; int magic_5; int total_sectors_high; int sector_size; int backup_time; int disk_offset_high; int disk_sectors_high; int disk_rebuild_high; int /*<<< orphan*/  rebuild_lba64; TYPE_2__* disks; int /*<<< orphan*/  volume_id; TYPE_1__ disk; } ;
struct TYPE_4__ {int flags; int number; int channel; int device; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int PROMISE_MAX_DISKS ; 
 int g_raid_debug ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
g_raid_md_promise_print(struct promise_raid_conf *meta)
{
	int i;

	if (g_raid_debug < 1)
		return;

	printf("********* ATA Promise Metadata *********\n");
	printf("promise_id          <%.24s>\n", meta->promise_id);
	printf("disk                %02x %02x %02x %02x %016jx\n",
	    meta->disk.flags, meta->disk.number, meta->disk.channel,
	    meta->disk.device, meta->disk.id);
	printf("disk_offset         %u\n", meta->disk_offset);
	printf("disk_sectors        %u\n", meta->disk_sectors);
	printf("disk_rebuild        %u\n", meta->disk_rebuild);
	printf("generation          %u\n", meta->generation);
	printf("status              0x%02x\n", meta->status);
	printf("type                %u\n", meta->type);
	printf("total_disks         %u\n", meta->total_disks);
	printf("stripe_shift        %u\n", meta->stripe_shift);
	printf("array_width         %u\n", meta->array_width);
	printf("array_number        %u\n", meta->array_number);
	printf("total_sectors       %u\n", meta->total_sectors);
	printf("cylinders           %u\n", meta->cylinders);
	printf("heads               %u\n", meta->heads);
	printf("sectors             %u\n", meta->sectors);
	printf("volume_id           0x%016jx\n", meta->volume_id);
	printf("disks:\n");
	for (i = 0; i < PROMISE_MAX_DISKS; i++ ) {
		printf("                    %02x %02x %02x %02x %016jx\n",
		    meta->disks[i].flags, meta->disks[i].number,
		    meta->disks[i].channel, meta->disks[i].device,
		    meta->disks[i].id);
	}
	printf("name                <%.32s>\n", meta->name);
	printf("magic_3             0x%08x\n", meta->magic_3);
	printf("rebuild_lba64       %ju\n", meta->rebuild_lba64);
	printf("magic_4             0x%08x\n", meta->magic_4);
	printf("magic_5             0x%08x\n", meta->magic_5);
	printf("total_sectors_high  0x%08x\n", meta->total_sectors_high);
	printf("sector_size         %u\n", meta->sector_size);
	printf("backup_time         %d\n", meta->backup_time);
	printf("disk_offset_high    0x%08x\n", meta->disk_offset_high);
	printf("disk_sectors_high   0x%08x\n", meta->disk_sectors_high);
	printf("disk_rebuild_high   0x%08x\n", meta->disk_rebuild_high);
	printf("=================================================\n");
}