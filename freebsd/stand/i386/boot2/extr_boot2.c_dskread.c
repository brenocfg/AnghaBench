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
typedef  scalar_t__ uint8_t ;
struct dos_partition {scalar_t__ dp_typ; int dp_flag; unsigned int dp_start; } ;
struct disklabel {scalar_t__ d_magic; scalar_t__ d_magic2; scalar_t__ d_type; size_t d_npartitions; TYPE_1__* d_partitions; } ;
struct TYPE_6__ {char* secbuf; } ;
struct TYPE_5__ {unsigned int start; scalar_t__ slice; size_t part; int /*<<< orphan*/  init; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {unsigned int p_offset; int /*<<< orphan*/  p_size; } ;

/* Variables and functions */
 scalar_t__ BASE_SLICE ; 
 scalar_t__ COMPATIBILITY_SLICE ; 
 scalar_t__ DISKMAGIC ; 
 int /*<<< orphan*/  DOSBBSECTOR ; 
 int DOSPARTOFF ; 
 scalar_t__ DOSPTYP_386BSD ; 
 scalar_t__ DTYPE_SCSI ; 
 int LABELOFFSET ; 
 unsigned int LABELSECTOR ; 
 unsigned int NDOSPART ; 
 size_t RAW_PART ; 
 int /*<<< orphan*/  TYPE_DA ; 
 scalar_t__ WHOLE_DISK_SLICE ; 
 TYPE_3__* dmadat ; 
 int drvread (void*,unsigned int,unsigned int) ; 
 TYPE_2__ dsk ; 
 int /*<<< orphan*/  dsk_meta ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 

__attribute__((used)) static int
dskread(void *buf, unsigned lba, unsigned nblk)
{
	struct dos_partition *dp;
	struct disklabel *d;
	char *sec;
	unsigned i;
	uint8_t sl;
	const char *reason;

	if (!dsk_meta) {
		sec = dmadat->secbuf;
		dsk.start = 0;
		if (drvread(sec, DOSBBSECTOR, 1))
			return (-1);
		dp = (void *)(sec + DOSPARTOFF);
		sl = dsk.slice;
		if (sl < BASE_SLICE) {
			for (i = 0; i < NDOSPART; i++)
				if (dp[i].dp_typ == DOSPTYP_386BSD &&
				    (dp[i].dp_flag & 0x80 || sl < BASE_SLICE)) {
					sl = BASE_SLICE + i;
					if (dp[i].dp_flag & 0x80 ||
					    dsk.slice == COMPATIBILITY_SLICE)
						break;
				}
			if (dsk.slice == WHOLE_DISK_SLICE)
				dsk.slice = sl;
		}
		if (sl != WHOLE_DISK_SLICE) {
			if (sl != COMPATIBILITY_SLICE)
				dp += sl - BASE_SLICE;
			if (dp->dp_typ != DOSPTYP_386BSD) {
				reason = "slice";
				goto error;
			}
			dsk.start = dp->dp_start;
		}
		if (drvread(sec, dsk.start + LABELSECTOR, 1))
			return (-1);
		d = (void *)(sec + LABELOFFSET);
		if (d->d_magic != DISKMAGIC || d->d_magic2 != DISKMAGIC) {
			if (dsk.part != RAW_PART) {
				reason = "label";
				goto error;
			}
		} else {
			if (!dsk.init) {
				if (d->d_type == DTYPE_SCSI)
					dsk.type = TYPE_DA;
				dsk.init++;
			}
			if (dsk.part >= d->d_npartitions ||
			    !d->d_partitions[dsk.part].p_size) {
				reason = "partition";
				goto error;
			}
			dsk.start += d->d_partitions[dsk.part].p_offset;
			dsk.start -= d->d_partitions[RAW_PART].p_offset;
		}
	}
	return (drvread(buf, dsk.start + lba, nblk));
error:
	printf("Invalid %s\n", reason);
	return (-1);
}