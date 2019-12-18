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
typedef  int /*<<< orphan*/  uint8_t ;
struct octeon_device {int dummy; } ;
struct TYPE_6__ {int cmd; int /*<<< orphan*/  param1; } ;
struct TYPE_7__ {TYPE_1__ s; scalar_t__ cmd64; } ;
struct lio_ctrl_pkt {int wait_time; int /*<<< orphan*/  cb_fn; struct lio* lio; int /*<<< orphan*/  iq_no; TYPE_2__ ncmd; } ;
struct TYPE_10__ {TYPE_4__* txpciq; } ;
struct lio {struct octeon_device* oct_dev; TYPE_5__ linfo; } ;
struct ifnet {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_9__ {TYPE_3__ s; } ;

/* Variables and functions */
 struct lio* if_getsoftc (struct ifnet*) ; 
 int /*<<< orphan*/  lio_ctrl_cmd_completion ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*,int) ; 
 int lio_send_ctrl_pkt (struct octeon_device*,struct lio_ctrl_pkt*) ; 

__attribute__((used)) static int
lio_set_rxcsum_command(struct ifnet *ifp, int command, uint8_t rx_cmd)
{
	struct lio_ctrl_pkt	nctrl;
	struct lio		*lio = if_getsoftc(ifp);
	struct octeon_device	*oct = lio->oct_dev;
	int	ret = 0;

	nctrl.ncmd.cmd64 = 0;
	nctrl.ncmd.s.cmd = command;
	nctrl.ncmd.s.param1 = rx_cmd;
	nctrl.iq_no = lio->linfo.txpciq[0].s.q_no;
	nctrl.wait_time = 100;
	nctrl.lio = lio;
	nctrl.cb_fn = lio_ctrl_cmd_completion;

	ret = lio_send_ctrl_pkt(lio->oct_dev, &nctrl);
	if (ret < 0) {
		lio_dev_err(oct, "DEVFLAGS RXCSUM change failed in core(ret:0x%x)\n",
			    ret);
	}

	return (ret);
}