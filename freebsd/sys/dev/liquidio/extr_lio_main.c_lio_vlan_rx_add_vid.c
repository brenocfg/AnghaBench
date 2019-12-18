#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct octeon_device {int dummy; } ;
struct TYPE_6__ {int param1; int /*<<< orphan*/  cmd; } ;
struct TYPE_7__ {TYPE_1__ s; scalar_t__ cmd64; } ;
struct lio_ctrl_pkt {int wait_time; int /*<<< orphan*/  cb_fn; struct lio* lio; int /*<<< orphan*/  iq_no; TYPE_2__ ncmd; } ;
struct TYPE_10__ {TYPE_4__* txpciq; } ;
struct lio {struct octeon_device* oct_dev; TYPE_5__ linfo; } ;
struct ifnet {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_9__ {TYPE_3__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_CMD_ADD_VLAN_FILTER ; 
 int /*<<< orphan*/  bzero (struct lio_ctrl_pkt*,int) ; 
 void* if_getsoftc (struct ifnet*) ; 
 int /*<<< orphan*/  lio_ctrl_cmd_completion ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*,int) ; 
 int lio_send_ctrl_pkt (struct octeon_device*,struct lio_ctrl_pkt*) ; 

__attribute__((used)) static void
lio_vlan_rx_add_vid(void *arg, struct ifnet *ifp, uint16_t vid)
{
	struct lio_ctrl_pkt	nctrl;
	struct lio		*lio = if_getsoftc(ifp);
	struct octeon_device	*oct = lio->oct_dev;
	int	ret = 0;

	if (if_getsoftc(ifp) != arg)	/* Not our event */
		return;

	if ((vid == 0) || (vid > 4095))	/* Invalid */
		return;

	bzero(&nctrl, sizeof(struct lio_ctrl_pkt));

	nctrl.ncmd.cmd64 = 0;
	nctrl.ncmd.s.cmd = LIO_CMD_ADD_VLAN_FILTER;
	nctrl.ncmd.s.param1 = vid;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.wait_time = 100;
	nctrl.lio = lio;
	nctrl.cb_fn = lio_ctrl_cmd_completion;

	ret = lio_send_ctrl_pkt(lio->oct_dev, &nctrl);
	if (ret < 0) {
		lio_dev_err(oct, "Add VLAN filter failed in core (ret: 0x%x)\n",
			    ret);
	}
}