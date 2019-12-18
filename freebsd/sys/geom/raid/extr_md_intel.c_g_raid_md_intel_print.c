#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_raid_vol {char* name; int reserved; int migr_priority; int num_sub_vols; int tid; int cng_master_disk; int cache_policy; int cng_state; int cng_sub_state; int curr_migr_unit; int curr_migr_unit_hi; int checkpoint_id; int migr_state; int migr_type; int dirty; int fs_state; int verify_errors; int bad_blocks; int /*<<< orphan*/  state; int /*<<< orphan*/  total_sectors; } ;
struct intel_raid_map {int offset; int offset_hi; int disk_sectors; int disk_sectors_hi; int stripe_count; int stripe_count_hi; int strip_sectors; int status; int type; int total_disks; int total_domains; int failed_disk_num; int ddf; int* disk_idx; } ;
struct intel_raid_conf {char* intel_id; char* version; int checksum; int config_size; int config_id; int generation; int error_log_size; int total_disks; int total_volumes; int error_log_pos; int cache_size; int orig_config_id; int pwr_cycle_count; int bbm_log_size; TYPE_1__* disk; int /*<<< orphan*/  attributes; } ;
struct TYPE_2__ {char* serial; int sectors; int sectors_hi; int id; int /*<<< orphan*/  owner_cfg_num; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int g_raid_debug ; 
 char* intel_cngst2str (int) ; 
 struct intel_raid_map* intel_get_map (struct intel_raid_vol*,int) ; 
 struct intel_raid_vol* intel_get_volume (struct intel_raid_conf*,int) ; 
 char* intel_mt2str (int) ; 
 char* intel_status2str (int) ; 
 char* intel_type2str (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
g_raid_md_intel_print(struct intel_raid_conf *meta)
{
	struct intel_raid_vol *mvol;
	struct intel_raid_map *mmap;
	int i, j, k;

	if (g_raid_debug < 1)
		return;

	printf("********* ATA Intel MatrixRAID Metadata *********\n");
	printf("intel_id            <%.24s>\n", meta->intel_id);
	printf("version             <%.6s>\n", meta->version);
	printf("checksum            0x%08x\n", meta->checksum);
	printf("config_size         0x%08x\n", meta->config_size);
	printf("config_id           0x%08x\n", meta->config_id);
	printf("generation          0x%08x\n", meta->generation);
	printf("error_log_size      %d\n", meta->error_log_size);
	printf("attributes          0x%b\n", meta->attributes,
		"\020"
		"\001RAID0"
		"\002RAID1"
		"\003RAID10"
		"\004RAID1E"
		"\005RAID15"
		"\006RAIDCNG"
		"\007EXT_STRIP"
		"\032NVM_CACHE"
		"\0332TB_DISK"
		"\034BBM"
		"\035NVM_CACHE"
		"\0362TB"
		"\037PM"
		"\040CHECKSUM");
	printf("total_disks         %u\n", meta->total_disks);
	printf("total_volumes       %u\n", meta->total_volumes);
	printf("error_log_pos       %u\n", meta->error_log_pos);
	printf("cache_size          %u\n", meta->cache_size);
	printf("orig_config_id      0x%08x\n", meta->orig_config_id);
	printf("pwr_cycle_count     %u\n", meta->pwr_cycle_count);
	printf("bbm_log_size        %u\n", meta->bbm_log_size);
	printf("Flags: S - Spare, A - Assigned, F - Failed, O - Online, D - Disabled\n");
	printf("DISK#   serial disk_sectors disk_sectors_hi disk_id flags owner\n");
	for (i = 0; i < meta->total_disks; i++ ) {
		printf("    %d   <%.16s> %u %u 0x%08x 0x%b %08x\n", i,
		    meta->disk[i].serial, meta->disk[i].sectors,
		    meta->disk[i].sectors_hi, meta->disk[i].id,
		    meta->disk[i].flags, "\20\01S\02A\03F\04O\05D",
		    meta->disk[i].owner_cfg_num);
	}
	for (i = 0; i < meta->total_volumes; i++) {
		mvol = intel_get_volume(meta, i);
		printf(" ****** Volume %d ******\n", i);
		printf(" name               %.16s\n", mvol->name);
		printf(" total_sectors      %ju\n", mvol->total_sectors);
		printf(" state              0x%b\n", mvol->state,
			"\020"
			"\001BOOTABLE"
			"\002BOOT_DEVICE"
			"\003READ_COALESCING"
			"\004WRITE_COALESCING"
			"\005LAST_SHUTDOWN_DIRTY"
			"\006HIDDEN_AT_BOOT"
			"\007CURRENTLY_HIDDEN"
			"\010VERIFY_AND_FIX"
			"\011MAP_STATE_UNINIT"
			"\012NO_AUTO_RECOVERY"
			"\013CLONE_N_GO"
			"\014CLONE_MAN_SYNC"
			"\015CNG_MASTER_DISK_NUM");
		printf(" reserved           %u\n", mvol->reserved);
		printf(" migr_priority      %u\n", mvol->migr_priority);
		printf(" num_sub_vols       %u\n", mvol->num_sub_vols);
		printf(" tid                %u\n", mvol->tid);
		printf(" cng_master_disk    %u\n", mvol->cng_master_disk);
		printf(" cache_policy       %u\n", mvol->cache_policy);
		printf(" cng_state          %u (%s)\n", mvol->cng_state,
			intel_cngst2str(mvol->cng_state));
		printf(" cng_sub_state      %u\n", mvol->cng_sub_state);
		printf(" curr_migr_unit     %u\n", mvol->curr_migr_unit);
		printf(" curr_migr_unit_hi  %u\n", mvol->curr_migr_unit_hi);
		printf(" checkpoint_id      %u\n", mvol->checkpoint_id);
		printf(" migr_state         %u\n", mvol->migr_state);
		printf(" migr_type          %u (%s)\n", mvol->migr_type,
			intel_mt2str(mvol->migr_type));
		printf(" dirty              %u\n", mvol->dirty);
		printf(" fs_state           %u\n", mvol->fs_state);
		printf(" verify_errors      %u\n", mvol->verify_errors);
		printf(" bad_blocks         %u\n", mvol->bad_blocks);

		for (j = 0; j < (mvol->migr_state ? 2 : 1); j++) {
			printf("  *** Map %d ***\n", j);
			mmap = intel_get_map(mvol, j);
			printf("  offset            %u\n", mmap->offset);
			printf("  offset_hi         %u\n", mmap->offset_hi);
			printf("  disk_sectors      %u\n", mmap->disk_sectors);
			printf("  disk_sectors_hi   %u\n", mmap->disk_sectors_hi);
			printf("  stripe_count      %u\n", mmap->stripe_count);
			printf("  stripe_count_hi   %u\n", mmap->stripe_count_hi);
			printf("  strip_sectors     %u\n", mmap->strip_sectors);
			printf("  status            %u (%s)\n", mmap->status,
				intel_status2str(mmap->status));
			printf("  type              %u (%s)\n", mmap->type,
				intel_type2str(mmap->type));
			printf("  total_disks       %u\n", mmap->total_disks);
			printf("  total_domains     %u\n", mmap->total_domains);
			printf("  failed_disk_num   %u\n", mmap->failed_disk_num);
			printf("  ddf               %u\n", mmap->ddf);
			printf("  disk_idx         ");
			for (k = 0; k < mmap->total_disks; k++)
				printf(" 0x%08x", mmap->disk_idx[k]);
			printf("\n");
		}
	}
	printf("=================================================\n");
}