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
struct ata_scsi_args {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ata_id_form_factor (int /*<<< orphan*/ ) ; 
 int ata_id_rotation_rate (int /*<<< orphan*/ ) ; 
 int ata_id_zoned_cap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int ata_scsiop_inq_b1(struct ata_scsi_args *args, u8 *rbuf)
{
	int form_factor = ata_id_form_factor(args->id);
	int media_rotation_rate = ata_id_rotation_rate(args->id);
	u8 zoned = ata_id_zoned_cap(args->id);

	rbuf[1] = 0xb1;
	rbuf[3] = 0x3c;
	rbuf[4] = media_rotation_rate >> 8;
	rbuf[5] = media_rotation_rate;
	rbuf[7] = form_factor;
	if (zoned)
		rbuf[8] = (zoned << 4);

	return 0;
}