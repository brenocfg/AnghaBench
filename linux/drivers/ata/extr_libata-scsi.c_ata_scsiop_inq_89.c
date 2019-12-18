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
typedef  int u8 ;
typedef  int /*<<< orphan*/  tf ;
struct ata_taskfile {int lbal; int nsect; int /*<<< orphan*/  command; } ;
struct ata_scsi_args {char* id; } ;

/* Variables and functions */
 int ATA_CMD_ID_ATA ; 
 int /*<<< orphan*/  ATA_DRDY ; 
 char* DRV_VERSION ; 
 int /*<<< orphan*/  ata_tf_to_fis (struct ata_taskfile*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  memcpy (int*,char*,int) ; 
 int /*<<< orphan*/  memset (struct ata_taskfile*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int ata_scsiop_inq_89(struct ata_scsi_args *args, u8 *rbuf)
{
	struct ata_taskfile tf;

	memset(&tf, 0, sizeof(tf));

	rbuf[1] = 0x89;			/* our page code */
	rbuf[2] = (0x238 >> 8);		/* page size fixed at 238h */
	rbuf[3] = (0x238 & 0xff);

	memcpy(&rbuf[8], "linux   ", 8);
	memcpy(&rbuf[16], "libata          ", 16);
	memcpy(&rbuf[32], DRV_VERSION, 4);

	/* we don't store the ATA device signature, so we fake it */

	tf.command = ATA_DRDY;		/* really, this is Status reg */
	tf.lbal = 0x1;
	tf.nsect = 0x1;

	ata_tf_to_fis(&tf, 0, 1, &rbuf[36]);	/* TODO: PMP? */
	rbuf[36] = 0x34;		/* force D2H Reg FIS (34h) */

	rbuf[56] = ATA_CMD_ID_ATA;

	memcpy(&rbuf[60], &args->id[0], 512);
	return 0;
}