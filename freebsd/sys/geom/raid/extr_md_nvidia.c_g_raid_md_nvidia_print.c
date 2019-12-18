#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvidia_raid_conf {char* nvidia_id; int config_size; int checksum; int version; int disk_number; int dummy_0; int total_sectors; int sector_size; char* name; int* revision; int disk_status; int magic_0; int state; int array_width; int total_disks; int orig_array_width; int type; int dummy_3; int strip_sectors; int strip_bytes; int strip_shift; int strip_mask; int stripe_sectors; int stripe_bytes; int rebuild_lba; int orig_type; int orig_total_sectors; int status; int /*<<< orphan*/ * volume_id; } ;

/* Variables and functions */
 int g_raid_debug ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
g_raid_md_nvidia_print(struct nvidia_raid_conf *meta)
{

	if (g_raid_debug < 1)
		return;

	printf("********* ATA NVIDIA RAID Metadata *********\n");
	printf("nvidia_id           <%.8s>\n", meta->nvidia_id);
	printf("config_size         %u\n", meta->config_size);
	printf("checksum            0x%08x\n", meta->checksum);
	printf("version             0x%04x\n", meta->version);
	printf("disk_number         %d\n", meta->disk_number);
	printf("dummy_0             0x%02x\n", meta->dummy_0);
	printf("total_sectors       %u\n", meta->total_sectors);
	printf("sector_size         %u\n", meta->sector_size);
	printf("name                <%.16s>\n", meta->name);
	printf("revision            0x%02x%02x%02x%02x\n",
	    meta->revision[0], meta->revision[1],
	    meta->revision[2], meta->revision[3]);
	printf("disk_status         0x%08x\n", meta->disk_status);
	printf("magic_0             0x%08x\n", meta->magic_0);
	printf("volume_id           0x%016jx%016jx\n",
	    meta->volume_id[1], meta->volume_id[0]);
	printf("state               0x%02x\n", meta->state);
	printf("array_width         %u\n", meta->array_width);
	printf("total_disks         %u\n", meta->total_disks);
	printf("orig_array_width    %u\n", meta->orig_array_width);
	printf("type                0x%04x\n", meta->type);
	printf("dummy_3             0x%04x\n", meta->dummy_3);
	printf("strip_sectors       %u\n", meta->strip_sectors);
	printf("strip_bytes         %u\n", meta->strip_bytes);
	printf("strip_shift         %u\n", meta->strip_shift);
	printf("strip_mask          0x%08x\n", meta->strip_mask);
	printf("stripe_sectors      %u\n", meta->stripe_sectors);
	printf("stripe_bytes        %u\n", meta->stripe_bytes);
	printf("rebuild_lba         %u\n", meta->rebuild_lba);
	printf("orig_type           0x%04x\n", meta->orig_type);
	printf("orig_total_sectors  %u\n", meta->orig_total_sectors);
	printf("status              0x%08x\n", meta->status);
	printf("=================================================\n");
}