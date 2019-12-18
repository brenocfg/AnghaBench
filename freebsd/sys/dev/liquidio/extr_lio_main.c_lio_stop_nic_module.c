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
struct TYPE_5__ {int /*<<< orphan*/  ifp; } ;
struct octeon_device {int ifcount; int num_oqs; TYPE_1__ props; int /*<<< orphan*/  cmd_resp_wqlock; int /*<<< orphan*/  cmd_resp_state; } ;
struct TYPE_8__ {TYPE_3__* rxpciq; } ;
struct lio {int /*<<< orphan*/  stats_timer; TYPE_4__ linfo; } ;
struct TYPE_6__ {int /*<<< orphan*/  q_no; } ;
struct TYPE_7__ {TYPE_2__ s; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIO_DRV_OFFLINE ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct lio* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lio_destroy_nic_device (struct octeon_device*,int) ; 
 int /*<<< orphan*/  lio_dev_dbg (struct octeon_device*,char*) ; 
 int /*<<< orphan*/  lio_dev_err (struct octeon_device*,char*) ; 
 int /*<<< orphan*/  lio_unregister_droq_ops (struct octeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lio_stop_nic_module(struct octeon_device *oct)
{
	int		i, j;
	struct lio	*lio;

	lio_dev_dbg(oct, "Stopping network interfaces\n");
	if (!oct->ifcount) {
		lio_dev_err(oct, "Init for Octeon was not completed\n");
		return (1);
	}

	mtx_lock(&oct->cmd_resp_wqlock);
	oct->cmd_resp_state = LIO_DRV_OFFLINE;
	mtx_unlock(&oct->cmd_resp_wqlock);

	for (i = 0; i < oct->ifcount; i++) {
		lio = if_getsoftc(oct->props.ifp);
		for (j = 0; j < oct->num_oqs; j++)
			lio_unregister_droq_ops(oct,
						lio->linfo.rxpciq[j].s.q_no);
	}

	callout_drain(&lio->stats_timer);

	for (i = 0; i < oct->ifcount; i++)
		lio_destroy_nic_device(oct, i);

	lio_dev_dbg(oct, "Network interface stopped\n");

	return (0);
}