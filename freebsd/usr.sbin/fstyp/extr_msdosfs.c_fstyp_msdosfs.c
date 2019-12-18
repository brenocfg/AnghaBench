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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int* BS_FilSysType; int* BS_VolLab; int BPB_NumFATs; int /*<<< orphan*/  BPB_BytsPerSec; int /*<<< orphan*/  BPB_FATSz32; int /*<<< orphan*/  BPB_RsvdSecCnt; } ;
struct TYPE_5__ {int* BS_FilSysType; int* BS_VolLab; int /*<<< orphan*/  BPB_FATSz16; } ;
struct TYPE_4__ {int* DIR_Name; int DIR_Attr; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ FAT_DES ;
typedef  TYPE_2__ FAT_BSBPB ;
typedef  TYPE_3__ FAT32_BSBPB ;

/* Variables and functions */
 int FAT_DES_ATTR_LONG_NAME ; 
 int FAT_DES_ATTR_VOLUME_ID ; 
 char* LABEL_NO_NAME ; 
 int /*<<< orphan*/  MIN (size_t,int) ; 
 scalar_t__ UINT16BYTES (int /*<<< orphan*/ ) ; 
 int UINT32BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ read_buf (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rtrim (char*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int*,char*,int) ; 

int
fstyp_msdosfs(FILE *fp, char *label, size_t size)
{
	FAT_BSBPB *pfat_bsbpb;
	FAT32_BSBPB *pfat32_bsbpb;
	FAT_DES *pfat_entry;
	uint8_t *sector0, *sector;

	sector0 = NULL;
	sector = NULL;

	/* Load 1st sector with boot sector and boot parameter block. */
	sector0 = (uint8_t *)read_buf(fp, 0, 512);
	if (sector0 == NULL)
		return (1);

	/* Check for the FAT boot sector signature. */
	if (sector0[510] != 0x55 || sector0[511] != 0xaa) {
		goto error;
	}

	/*
	 * Test if this is really a FAT volume and determine the FAT type.
	 */

	pfat_bsbpb = (FAT_BSBPB *)sector0;
	pfat32_bsbpb = (FAT32_BSBPB *)sector0;

	if (UINT16BYTES(pfat_bsbpb->BPB_FATSz16) != 0) {
		/*
		 * If the BPB_FATSz16 field is not zero and the string "FAT" is
		 * at the right place, this should be a FAT12 or FAT16 volume.
		 */
		if (strncmp(pfat_bsbpb->BS_FilSysType, "FAT", 3) != 0) {
			goto error;
		}

		/* A volume with no name should have "NO NAME    " as label. */
		if (strncmp(pfat_bsbpb->BS_VolLab, LABEL_NO_NAME,
		    sizeof(pfat_bsbpb->BS_VolLab)) == 0) {
			goto endofchecks;
		}
		strlcpy(label, pfat_bsbpb->BS_VolLab,
		    MIN(size, sizeof(pfat_bsbpb->BS_VolLab) + 1));
	} else if (UINT32BYTES(pfat32_bsbpb->BPB_FATSz32) != 0) {
		uint32_t fat_FirstDataSector, fat_BytesPerSector, offset;

		/*
		 * If the BPB_FATSz32 field is not zero and the string "FAT" is
		 * at the right place, this should be a FAT32 volume.
		 */
		if (strncmp(pfat32_bsbpb->BS_FilSysType, "FAT", 3) != 0) {
			goto error;
		}

		/*
		 * If the volume label is not "NO NAME    " we're done.
		 */
		if (strncmp(pfat32_bsbpb->BS_VolLab, LABEL_NO_NAME,
		    sizeof(pfat32_bsbpb->BS_VolLab)) != 0) {
			strlcpy(label, pfat32_bsbpb->BS_VolLab,
			    MIN(size, sizeof(pfat32_bsbpb->BS_VolLab) + 1));
			goto endofchecks;
		}

		/*
		 * If the volume label "NO NAME    " is in the boot sector, the
		 * label of FAT32 volumes may be stored as a special entry in
		 * the root directory.
		 */
		fat_FirstDataSector =
		    UINT16BYTES(pfat32_bsbpb->BPB_RsvdSecCnt) +
		    (pfat32_bsbpb->BPB_NumFATs *
		     UINT32BYTES(pfat32_bsbpb->BPB_FATSz32));
		fat_BytesPerSector = UINT16BYTES(pfat32_bsbpb->BPB_BytsPerSec);

		//    fat_FirstDataSector, fat_BytesPerSector);

		for (offset = fat_BytesPerSector * fat_FirstDataSector;;
		    offset += fat_BytesPerSector) {
			sector = (uint8_t *)read_buf(fp, offset, fat_BytesPerSector);
			if (sector == NULL)
				goto error;

			pfat_entry = (FAT_DES *)sector;
			do {
				/* No more entries available. */
				if (pfat_entry->DIR_Name[0] == 0) {
					goto endofchecks;
				}

				/* Skip empty or long name entries. */
				if (pfat_entry->DIR_Name[0] == 0xe5 ||
				    (pfat_entry->DIR_Attr &
				     FAT_DES_ATTR_LONG_NAME) ==
				    FAT_DES_ATTR_LONG_NAME) {
					continue;
				}

				/*
				 * The name of the entry is the volume label if
				 * ATTR_VOLUME_ID is set.
				 */
				if (pfat_entry->DIR_Attr &
				    FAT_DES_ATTR_VOLUME_ID) {
					strlcpy(label, pfat_entry->DIR_Name,
					    MIN(size,
					    sizeof(pfat_entry->DIR_Name) + 1));
					goto endofchecks;
				}
			} while((uint8_t *)(++pfat_entry) <
			    (uint8_t *)(sector + fat_BytesPerSector));
			free(sector);
		}
	} else {
		goto error;
	}

endofchecks:
	rtrim(label, size);

	free(sector0);
	free(sector);

	return (0);

error:
	free(sector0);
	free(sector);

	return (1);
}