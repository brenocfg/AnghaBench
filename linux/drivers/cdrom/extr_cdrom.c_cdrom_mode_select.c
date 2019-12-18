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
struct packet_command {int* cmd; int* buffer; int buflen; int /*<<< orphan*/  data_direction; } ;
struct cdrom_device_ops {int (* generic_packet ) (struct cdrom_device_info*,struct packet_command*) ;} ;
struct cdrom_device_info {struct cdrom_device_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGC_DATA_WRITE ; 
 int GPCMD_MODE_SELECT_10 ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct cdrom_device_info*,struct packet_command*) ; 

int cdrom_mode_select(struct cdrom_device_info *cdi,
		      struct packet_command *cgc)
{
	const struct cdrom_device_ops *cdo = cdi->ops;

	memset(cgc->cmd, 0, sizeof(cgc->cmd));
	memset(cgc->buffer, 0, 2);
	cgc->cmd[0] = GPCMD_MODE_SELECT_10;
	cgc->cmd[1] = 0x10;		/* PF */
	cgc->cmd[7] = cgc->buflen >> 8;
	cgc->cmd[8] = cgc->buflen & 0xff;
	cgc->data_direction = CGC_DATA_WRITE;
	return cdo->generic_packet(cdi, cgc);
}