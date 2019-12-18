#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mlx4_wqe_datagram_seg {int /*<<< orphan*/  mac; int /*<<< orphan*/  vlan; void* qkey; void* dqpn; int /*<<< orphan*/  av; } ;
struct mlx4_av {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ah; int /*<<< orphan*/  remote_qkey; int /*<<< orphan*/  remote_qpn; } ;
struct TYPE_5__ {TYPE_1__ ud; } ;
struct ibv_send_wr {TYPE_2__ wr; } ;
struct TYPE_6__ {int /*<<< orphan*/ * mac; int /*<<< orphan*/  vlan; int /*<<< orphan*/  av; } ;

/* Variables and functions */
 int /*<<< orphan*/  htobe16 (int /*<<< orphan*/ ) ; 
 void* htobe32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 TYPE_3__* to_mah (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_datagram_seg(struct mlx4_wqe_datagram_seg *dseg,
			     struct ibv_send_wr *wr)
{
	memcpy(dseg->av, &to_mah(wr->wr.ud.ah)->av, sizeof (struct mlx4_av));
	dseg->dqpn = htobe32(wr->wr.ud.remote_qpn);
	dseg->qkey = htobe32(wr->wr.ud.remote_qkey);
	dseg->vlan = htobe16(to_mah(wr->wr.ud.ah)->vlan);
	memcpy(dseg->mac, to_mah(wr->wr.ud.ah)->mac, 6);
}