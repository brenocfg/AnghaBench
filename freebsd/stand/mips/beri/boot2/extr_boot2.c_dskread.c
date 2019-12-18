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
struct dos_partition {scalar_t__ dp_typ; int dp_flag; int /*<<< orphan*/  dp_start; } ;
struct disklabel {TYPE_1__* d_partitions; int /*<<< orphan*/  d_npartitions; int /*<<< orphan*/  d_type; int /*<<< orphan*/  d_magic2; int /*<<< orphan*/  d_magic; } ;
struct TYPE_6__ {char* secbuf; } ;
struct TYPE_5__ {scalar_t__ start; scalar_t__ slice; size_t part; int /*<<< orphan*/  init; int /*<<< orphan*/  type; } ;
struct TYPE_4__ {int /*<<< orphan*/  p_offset; int /*<<< orphan*/  p_size; } ;

/* Variables and functions */
 scalar_t__ BASE_SLICE ; 
 scalar_t__ COMPATIBILITY_SLICE ; 
 scalar_t__ DISKMAGIC ; 
 int /*<<< orphan*/  DOSBBSECTOR ; 
 int DOSPARTOFF ; 
 scalar_t__ DOSPTYP_386BSD ; 
 scalar_t__ DTYPE_SCSI ; 
 int LABELOFFSET ; 
 scalar_t__ LABELSECTOR ; 
 unsigned int NDOSPART ; 
 size_t RAW_PART ; 
 int /*<<< orphan*/  TYPE_DA ; 
 scalar_t__ WHOLE_DISK_SLICE ; 
 TYPE_3__* dmadat ; 
 int drvread (void*,unsigned int,unsigned int) ; 
 TYPE_2__ dsk ; 
 int /*<<< orphan*/  dsk_meta ; 
 scalar_t__ le16toh (int /*<<< orphan*/ ) ; 
 scalar_t__ le32toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int
dskread(void *buf, unsigned lba, unsigned nblk)
{
#if 0
    /*
     * XXXRW: For now, assume no partition table around the file system; it's
     * just in raw flash.
     */
    struct dos_partition *dp;
    struct disklabel *d;
    char *sec;
    unsigned i;
    uint8_t sl;

    if (!dsk_meta) {
	sec = dmadat->secbuf;
	dsk.start = 0;
	if (drvread(sec, DOSBBSECTOR, 1))
	    return -1;
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
		printf("Invalid %s\n", "slice");
		return -1;
	    }
	    dsk.start = le32toh(dp->dp_start);
	}
	if (drvread(sec, dsk.start + LABELSECTOR, 1))
		return -1;
	d = (void *)(sec + LABELOFFSET);
	if (le32toh(d->d_magic) != DISKMAGIC ||
	    le32toh(d->d_magic2) != DISKMAGIC) {
	    if (dsk.part != RAW_PART) {
		printf("Invalid %s\n", "label");
		return -1;
	    }
	} else {
	    if (!dsk.init) {
		if (le16toh(d->d_type) == DTYPE_SCSI)
		    dsk.type = TYPE_DA;
		dsk.init++;
	    }
	    if (dsk.part >= le16toh(d->d_npartitions) ||
		!(le32toh(d->d_partitions[dsk.part].p_size))) {
		printf("Invalid %s\n", "partition");
		return -1;
	    }
	    dsk.start += le32toh(d->d_partitions[dsk.part].p_offset);
	    dsk.start -= le32toh(d->d_partitions[RAW_PART].p_offset);
	}
    }
    return drvread(buf, dsk.start + lba, nblk);
#else
    return drvread(buf, lba, nblk);
#endif
}