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
struct TYPE_2__ {int flags; int control; } ;
struct ccb_ataio {TYPE_1__ cmd; } ;

/* Variables and functions */
 int CAM_ATAIO_CONTROL ; 
 int CAM_ATAIO_NEEDRESULT ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 

void
ata_reset_cmd(struct ccb_ataio *ataio)
{
	bzero(&ataio->cmd, sizeof(ataio->cmd));
	ataio->cmd.flags = CAM_ATAIO_CONTROL | CAM_ATAIO_NEEDRESULT;
	ataio->cmd.control = 0x04;
}