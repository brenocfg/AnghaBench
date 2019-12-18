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
struct packet_command {int* cmd; int quiet; } ;
struct cdrom_device_info {int mmc3_profile; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  buffer ;
struct TYPE_2__ {int (* generic_packet ) (struct cdrom_device_info*,struct packet_command*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CGC_DATA_READ ; 
 int GPCMD_GET_CONFIGURATION ; 
 int /*<<< orphan*/  init_cdrom_command (struct packet_command*,char*,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct cdrom_device_info*,struct packet_command*) ; 

__attribute__((used)) static void cdrom_mmc3_profile(struct cdrom_device_info *cdi)
{
	struct packet_command cgc;
	char buffer[32];
	int ret, mmc3_profile;

	init_cdrom_command(&cgc, buffer, sizeof(buffer), CGC_DATA_READ);

	cgc.cmd[0] = GPCMD_GET_CONFIGURATION;
	cgc.cmd[1] = 0;
	cgc.cmd[2] = cgc.cmd[3] = 0;		/* Starting Feature Number */
	cgc.cmd[8] = sizeof(buffer);		/* Allocation Length */
	cgc.quiet = 1;

	if ((ret = cdi->ops->generic_packet(cdi, &cgc)))
		mmc3_profile = 0xffff;
	else
		mmc3_profile = (buffer[6] << 8) | buffer[7];

	cdi->mmc3_profile = mmc3_profile;
}