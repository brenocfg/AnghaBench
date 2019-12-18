#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockopt {scalar_t__ sopt_level; int sopt_dir; int /*<<< orphan*/  sopt_name; } ;
struct socket {int dummy; } ;
struct ng_btsocket_rfcomm_fc_info {int cfc; int /*<<< orphan*/  reserved; int /*<<< orphan*/  rx_cred; int /*<<< orphan*/  tx_cred; int /*<<< orphan*/  rmodem; int /*<<< orphan*/  lmodem; } ;
typedef  TYPE_1__* ng_btsocket_rfcomm_pcb_p ;
typedef  int /*<<< orphan*/  fcinfo ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  pcb_mtx; int /*<<< orphan*/  rx_cred; int /*<<< orphan*/  tx_cred; int /*<<< orphan*/  rmodem; int /*<<< orphan*/  lmodem; struct ng_btsocket_rfcomm_fc_info mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOPROTOOPT ; 
 int NG_BTSOCKET_RFCOMM_DLC_CFC ; 
 scalar_t__ SOL_RFCOMM ; 
#define  SOPT_GET 131 
#define  SOPT_SET 130 
#define  SO_RFCOMM_FC_INFO 129 
#define  SO_RFCOMM_MTU 128 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* so2rfcomm_pcb (struct socket*) ; 
 int sooptcopyout (struct sockopt*,struct ng_btsocket_rfcomm_fc_info*,int) ; 

int
ng_btsocket_rfcomm_ctloutput(struct socket *so, struct sockopt *sopt)
{
	ng_btsocket_rfcomm_pcb_p		pcb = so2rfcomm_pcb(so);
	struct ng_btsocket_rfcomm_fc_info	fcinfo;
	int					error = 0;

	if (pcb == NULL)
		return (EINVAL);
	if (sopt->sopt_level != SOL_RFCOMM)
		return (0);

	mtx_lock(&pcb->pcb_mtx);

	switch (sopt->sopt_dir) {
	case SOPT_GET:
		switch (sopt->sopt_name) {
		case SO_RFCOMM_MTU:
			error = sooptcopyout(sopt, &pcb->mtu, sizeof(pcb->mtu));
			break;

		case SO_RFCOMM_FC_INFO:
			fcinfo.lmodem = pcb->lmodem;
			fcinfo.rmodem = pcb->rmodem;
			fcinfo.tx_cred = pcb->tx_cred;
			fcinfo.rx_cred = pcb->rx_cred;
			fcinfo.cfc = (pcb->flags & NG_BTSOCKET_RFCOMM_DLC_CFC)?
				1 : 0;
			fcinfo.reserved = 0;

			error = sooptcopyout(sopt, &fcinfo, sizeof(fcinfo));
			break;

		default:
			error = ENOPROTOOPT;
			break;
		}
		break;

	case SOPT_SET:
		switch (sopt->sopt_name) {
		default:
			error = ENOPROTOOPT;
			break;
		}
		break;

	default:
		error = EINVAL;
		break;
	}

	mtx_unlock(&pcb->pcb_mtx);

	return (error);
}