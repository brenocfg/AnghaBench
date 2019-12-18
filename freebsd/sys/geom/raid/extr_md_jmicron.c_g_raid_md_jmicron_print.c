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
struct jmicron_raid_conf {int* signature; int version; int checksum; int disk_id; int offset; int disk_sectors_high; int disk_sectors_low; char* name; int type; int stripe_shift; int flags; int* spare; int* disks; } ;

/* Variables and functions */
 int JMICRON_MAX_DISKS ; 
 int JMICRON_MAX_SPARE ; 
 int g_raid_debug ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
g_raid_md_jmicron_print(struct jmicron_raid_conf *meta)
{
	int k;

	if (g_raid_debug < 1)
		return;

	printf("********* ATA JMicron RAID Metadata *********\n");
	printf("signature           <%c%c>\n", meta->signature[0], meta->signature[1]);
	printf("version             %04x\n", meta->version);
	printf("checksum            0x%04x\n", meta->checksum);
	printf("disk_id             0x%08x\n", meta->disk_id);
	printf("offset              0x%08x\n", meta->offset);
	printf("disk_sectors_high   0x%08x\n", meta->disk_sectors_high);
	printf("disk_sectors_low    0x%04x\n", meta->disk_sectors_low);
	printf("name                <%.16s>\n", meta->name);
	printf("type                %d\n", meta->type);
	printf("stripe_shift        %d\n", meta->stripe_shift);
	printf("flags               %04x\n", meta->flags);
	printf("spare              ");
	for (k = 0; k < JMICRON_MAX_SPARE; k++)
		printf(" 0x%08x", meta->spare[k]);
	printf("\n");
	printf("disks              ");
	for (k = 0; k < JMICRON_MAX_DISKS; k++)
		printf(" 0x%08x", meta->disks[k]);
	printf("\n");
	printf("=================================================\n");
}