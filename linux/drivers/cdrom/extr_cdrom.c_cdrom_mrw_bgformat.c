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
struct packet_command {int* cmd; int timeout; } ;
struct cdrom_device_info {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int (* generic_packet ) (struct cdrom_device_info*,struct packet_command*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CGC_DATA_WRITE ; 
 int GPCMD_FORMAT_UNIT ; 
 int HZ ; 
 int /*<<< orphan*/  init_cdrom_command (struct packet_command*,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int stub1 (struct cdrom_device_info*,struct packet_command*) ; 

__attribute__((used)) static int cdrom_mrw_bgformat(struct cdrom_device_info *cdi, int cont)
{
	struct packet_command cgc;
	unsigned char buffer[12];
	int ret;

	pr_info("%sstarting format\n", cont ? "Re" : "");

	/*
	 * FmtData bit set (bit 4), format type is 1
	 */
	init_cdrom_command(&cgc, buffer, sizeof(buffer), CGC_DATA_WRITE);
	cgc.cmd[0] = GPCMD_FORMAT_UNIT;
	cgc.cmd[1] = (1 << 4) | 1;

	cgc.timeout = 5 * 60 * HZ;

	/*
	 * 4 byte format list header, 8 byte format list descriptor
	 */
	buffer[1] = 1 << 1;
	buffer[3] = 8;

	/*
	 * nr_blocks field
	 */
	buffer[4] = 0xff;
	buffer[5] = 0xff;
	buffer[6] = 0xff;
	buffer[7] = 0xff;

	buffer[8] = 0x24 << 2;
	buffer[11] = cont;

	ret = cdi->ops->generic_packet(cdi, &cgc);
	if (ret)
		pr_info("bgformat failed\n");

	return ret;
}