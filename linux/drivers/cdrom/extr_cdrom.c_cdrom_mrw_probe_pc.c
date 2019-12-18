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
struct packet_command {int quiet; int /*<<< orphan*/  timeout; } ;
struct cdrom_device_info {void* mrw_mode_page; } ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  CGC_DATA_READ ; 
 int /*<<< orphan*/  HZ ; 
 void* MRW_MODE_PC ; 
 void* MRW_MODE_PC_PRE1 ; 
 int /*<<< orphan*/  cdrom_mode_sense (struct cdrom_device_info*,struct packet_command*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_cdrom_command (struct packet_command*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdrom_mrw_probe_pc(struct cdrom_device_info *cdi)
{
	struct packet_command cgc;
	char buffer[16];

	init_cdrom_command(&cgc, buffer, sizeof(buffer), CGC_DATA_READ);

	cgc.timeout = HZ;
	cgc.quiet = 1;

	if (!cdrom_mode_sense(cdi, &cgc, MRW_MODE_PC, 0)) {
		cdi->mrw_mode_page = MRW_MODE_PC;
		return 0;
	} else if (!cdrom_mode_sense(cdi, &cgc, MRW_MODE_PC_PRE1, 0)) {
		cdi->mrw_mode_page = MRW_MODE_PC_PRE1;
		return 0;
	}

	return 1;
}