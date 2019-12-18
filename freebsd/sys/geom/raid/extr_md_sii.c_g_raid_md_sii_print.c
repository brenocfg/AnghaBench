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
struct sii_raid_conf {int product_id; int vendor_id; int version_minor; int version_major; int* timestamp; int strip_sectors; int disk_number; int type; int raid0_disks; int raid0_ident; int raid1_disks; int raid1_ident; int generation; int disk_status; int raid_status; int raid_location; int disk_location; int auto_rebuild; char* name; int checksum; scalar_t__ rebuild_lba; scalar_t__ total_sectors; } ;

/* Variables and functions */
 int g_raid_debug ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
g_raid_md_sii_print(struct sii_raid_conf *meta)
{

	if (g_raid_debug < 1)
		return;

	printf("********* ATA SiI RAID Metadata *********\n");
	printf("total_sectors       %llu\n",
	    (long long unsigned)meta->total_sectors);
	printf("product_id          0x%04x\n", meta->product_id);
	printf("vendor_id           0x%04x\n", meta->vendor_id);
	printf("version_minor       0x%04x\n", meta->version_minor);
	printf("version_major       0x%04x\n", meta->version_major);
	printf("timestamp           0x%02x%02x%02x%02x%02x%02x\n",
	    meta->timestamp[5], meta->timestamp[4], meta->timestamp[3],
	    meta->timestamp[2], meta->timestamp[1], meta->timestamp[0]);
	printf("strip_sectors       %d\n", meta->strip_sectors);
	printf("disk_number         %d\n", meta->disk_number);
	printf("type                0x%02x\n", meta->type);
	printf("raid0_disks         %d\n", meta->raid0_disks);
	printf("raid0_ident         %d\n", meta->raid0_ident);
	printf("raid1_disks         %d\n", meta->raid1_disks);
	printf("raid1_ident         %d\n", meta->raid1_ident);
	printf("rebuild_lba         %llu\n",
	    (long long unsigned)meta->rebuild_lba);
	printf("generation          %d\n", meta->generation);
	printf("disk_status         %d\n", meta->disk_status);
	printf("raid_status         %d\n", meta->raid_status);
	printf("raid_location       %d\n", meta->raid_location);
	printf("disk_location       %d\n", meta->disk_location);
	printf("auto_rebuild        %d\n", meta->auto_rebuild);
	printf("name                <%.16s>\n", meta->name);
	printf("checksum            0x%04x\n", meta->checksum);
	printf("=================================================\n");
}