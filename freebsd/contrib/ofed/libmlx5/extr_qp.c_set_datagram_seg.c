#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* qkey; } ;
struct TYPE_8__ {TYPE_1__ qkey; } ;
struct TYPE_12__ {TYPE_2__ key; void* dqp_dct; } ;
struct mlx5_wqe_datagram_seg {TYPE_6__ av; } ;
struct TYPE_9__ {int remote_qpn; int remote_qkey; int /*<<< orphan*/  ah; } ;
struct TYPE_10__ {TYPE_3__ ud; } ;
struct ibv_send_wr {TYPE_4__ wr; } ;
struct TYPE_11__ {int /*<<< orphan*/  av; } ;

/* Variables and functions */
 int MLX5_EXTENDED_UD_AV ; 
 void* htobe32 (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_6__*,int /*<<< orphan*/ *,int) ; 
 TYPE_5__* to_mah (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_datagram_seg(struct mlx5_wqe_datagram_seg *dseg,
			     struct ibv_send_wr *wr)
{
	memcpy(&dseg->av, &to_mah(wr->wr.ud.ah)->av, sizeof dseg->av);
	dseg->av.dqp_dct = htobe32(wr->wr.ud.remote_qpn | MLX5_EXTENDED_UD_AV);
	dseg->av.key.qkey.qkey = htobe32(wr->wr.ud.remote_qkey);
}