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
typedef  int /*<<< orphan*/  uint64_t ;
struct mtlocate {int dest_type; int /*<<< orphan*/  block_address_mode; int /*<<< orphan*/  partition; int /*<<< orphan*/  flags; int /*<<< orphan*/  logical_id; } ;
typedef  int /*<<< orphan*/  mtl ;
typedef  int mt_locate_dest_type ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTIOCEXTLOCATE ; 
 int /*<<< orphan*/  MT_LOCATE_BAM_EXPLICIT ; 
 int /*<<< orphan*/  MT_LOCATE_BAM_IMPLICIT ; 
#define  MT_LOCATE_DEST_EOD 131 
#define  MT_LOCATE_DEST_FILE 130 
#define  MT_LOCATE_DEST_OBJECT 129 
#define  MT_LOCATE_DEST_SET 128 
 int /*<<< orphan*/  MT_LOCATE_FLAG_CHANGE_PART ; 
 int /*<<< orphan*/  MT_LOCATE_FLAG_IMMED ; 
 int /*<<< orphan*/  bzero (struct mtlocate*,int) ; 
 int /*<<< orphan*/  err (int,char*,char const*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int getopt (int,char**,char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,struct mtlocate*) ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoull (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt_locate(int argc, char **argv, int mtfd, const char *tape)
{
	struct mtlocate mtl;
	uint64_t logical_id = 0;
	mt_locate_dest_type dest_type = MT_LOCATE_DEST_FILE;
	int eod = 0, explicit = 0, immediate = 0;
	int64_t partition = 0;
	int block_addr_set = 0, partition_set = 0, file_set = 0, set_set = 0;
	int c, retval;

	retval = 0;
	bzero(&mtl, sizeof(mtl));

	while ((c = getopt(argc, argv, "b:eEf:ip:s:")) != -1) {
		switch (c) {
		case 'b':
			/* Block address */
			logical_id = strtoull(optarg, NULL, 0);
			dest_type = MT_LOCATE_DEST_OBJECT;
			block_addr_set = 1;
			break;
		case 'e':
			/* end of data */
			eod = 1;
			dest_type = MT_LOCATE_DEST_EOD;
			break;
		case 'E':
			/*
			 * XXX KDM explicit address mode.  Should we even
			 * allow this, since the driver doesn't operate in
			 * explicit address mode?
			 */
			explicit = 1;
			break;
		case 'f':
			/* file number */
			logical_id = strtoull(optarg, NULL, 0);
			dest_type = MT_LOCATE_DEST_FILE;
			file_set = 1;
			break;
		case 'i':
			/*
			 * Immediate address mode.  XXX KDM do we want to
			 * implement this?  The other commands in the
			 * tape driver will need to be able to handle this.
			 */
			immediate = 1;
			break;
		case 'p':
			/*
			 * Change partition to the given partition.
			 */
			partition = strtol(optarg, NULL, 0);
			partition_set = 1;
			break;
		case 's':
			/* Go to the given set mark */
			logical_id = strtoull(optarg, NULL, 0);
			dest_type = MT_LOCATE_DEST_SET;
			set_set = 1;
			break;
		default:
			break;
		}
	}

	/*
	 * These options are mutually exclusive.  The user may only specify
	 * one.
	 */
	if ((block_addr_set + file_set + eod + set_set) != 1)
		errx(1, "You must specify only one of -b, -f, -e, or -s");

	mtl.dest_type = dest_type;
	switch (dest_type) {
	case MT_LOCATE_DEST_OBJECT:
	case MT_LOCATE_DEST_FILE:
	case MT_LOCATE_DEST_SET:
		mtl.logical_id = logical_id;
		break;
	case MT_LOCATE_DEST_EOD:
		break;
	}

	if (immediate != 0)
		mtl.flags |= MT_LOCATE_FLAG_IMMED;

	if (partition_set != 0) {
		mtl.flags |= MT_LOCATE_FLAG_CHANGE_PART;
		mtl.partition = partition;
	}

	if (explicit != 0)
		mtl.block_address_mode = MT_LOCATE_BAM_EXPLICIT;
	else
		mtl.block_address_mode = MT_LOCATE_BAM_IMPLICIT;

	if (ioctl(mtfd, MTIOCEXTLOCATE, &mtl) == -1)
		err(1, "MTIOCEXTLOCATE ioctl failed on %s", tape);

	return (retval);
}