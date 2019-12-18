#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  task_status; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  nexus; } ;
union ctl_io {TYPE_4__ taskio; TYPE_3__ io_hdr; } ;
struct TYPE_6__ {int /*<<< orphan*/ * serializing_sc; int /*<<< orphan*/ * original_sc; int /*<<< orphan*/  msg_type; int /*<<< orphan*/  nexus; } ;
struct TYPE_5__ {int /*<<< orphan*/  task_action; } ;
union ctl_ha_msg {TYPE_2__ hdr; TYPE_1__ task; } ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ctl_softc {int dummy; } ;

/* Variables and functions */
 int CTL_FLAG_FROM_OTHER_SC ; 
 int /*<<< orphan*/  CTL_HA_CHAN_CTL ; 
 int /*<<< orphan*/  CTL_MSG_MANAGE_TASKS ; 
 struct ctl_softc* CTL_SOFTC (union ctl_io*) ; 
 int /*<<< orphan*/  CTL_TASK_FUNCTION_COMPLETE ; 
 int /*<<< orphan*/  CTL_TASK_I_T_NEXUS_RESET ; 
 int /*<<< orphan*/  CTL_UA_I_T_NEXUS_LOSS ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  ctl_get_initindex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_ha_msg_send (int /*<<< orphan*/ ,union ctl_ha_msg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_i_t_nexus_loss (struct ctl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ctl_i_t_nexus_reset(union ctl_io *io)
{
	struct ctl_softc *softc = CTL_SOFTC(io);
	uint32_t initidx;

	if (!(io->io_hdr.flags & CTL_FLAG_FROM_OTHER_SC)) {
		union ctl_ha_msg msg_info;

		msg_info.hdr.nexus = io->io_hdr.nexus;
		msg_info.task.task_action = CTL_TASK_I_T_NEXUS_RESET;
		msg_info.hdr.msg_type = CTL_MSG_MANAGE_TASKS;
		msg_info.hdr.original_sc = NULL;
		msg_info.hdr.serializing_sc = NULL;
		ctl_ha_msg_send(CTL_HA_CHAN_CTL, &msg_info,
		    sizeof(msg_info.task), M_WAITOK);
	}

	initidx = ctl_get_initindex(&io->io_hdr.nexus);
	ctl_i_t_nexus_loss(softc, initidx, CTL_UA_I_T_NEXUS_LOSS);
	io->taskio.task_status = CTL_TASK_FUNCTION_COMPLETE;
	return (0);
}