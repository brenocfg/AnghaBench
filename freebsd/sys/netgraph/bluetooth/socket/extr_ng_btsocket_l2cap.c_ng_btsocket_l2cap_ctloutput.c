#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v ;
struct sockopt {scalar_t__ sopt_level; int sopt_dir; int /*<<< orphan*/  sopt_name; } ;
struct socket {int dummy; } ;
struct TYPE_5__ {int mtu; int flush_timo; int /*<<< orphan*/  encryption; int /*<<< orphan*/  flow; } ;
typedef  TYPE_1__ ng_l2cap_cfg_opt_val_t ;
typedef  TYPE_2__* ng_btsocket_l2cap_pcb_p ;
struct TYPE_6__ {int imtu; int omtu; int iflow; int oflow; int flush_timo; int need_encrypt; int /*<<< orphan*/  pcb_mtx; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int ENOPROTOOPT ; 
 int /*<<< orphan*/  NG_BTSOCKET_L2CAP_CLOSED ; 
 int /*<<< orphan*/  NG_BTSOCKET_L2CAP_OPEN ; 
 int /*<<< orphan*/  NG_BTSOCKET_L2CAP_W4_ENC_CHANGE ; 
 scalar_t__ SOL_L2CAP ; 
#define  SOPT_GET 135 
#define  SOPT_SET 134 
#define  SO_L2CAP_ENCRYPTED 133 
#define  SO_L2CAP_FLUSH 132 
#define  SO_L2CAP_IFLOW 131 
#define  SO_L2CAP_IMTU 130 
#define  SO_L2CAP_OFLOW 129 
#define  SO_L2CAP_OMTU 128 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ng_btsocket_l2cap_node ; 
 TYPE_2__* so2l2cap_pcb (struct socket*) ; 
 int sooptcopyin (struct sockopt*,TYPE_1__*,int,int) ; 
 int sooptcopyout (struct sockopt*,int*,int) ; 

int
ng_btsocket_l2cap_ctloutput(struct socket *so, struct sockopt *sopt)
{
	ng_btsocket_l2cap_pcb_p	pcb = so2l2cap_pcb(so);
	int			error = 0;
	ng_l2cap_cfg_opt_val_t	v;

	if (pcb == NULL)
		return (EINVAL);
	if (ng_btsocket_l2cap_node == NULL) 
		return (EINVAL);

	if (sopt->sopt_level != SOL_L2CAP)
		return (0);

	mtx_lock(&pcb->pcb_mtx);

	switch (sopt->sopt_dir) {
	case SOPT_GET:
		switch (sopt->sopt_name) {
		case SO_L2CAP_IMTU: /* get incoming MTU */
			error = sooptcopyout(sopt, &pcb->imtu,
						sizeof(pcb->imtu));
			break;

		case SO_L2CAP_OMTU: /* get outgoing (peer incoming) MTU */
			error = sooptcopyout(sopt, &pcb->omtu,
						sizeof(pcb->omtu));
			break;

		case SO_L2CAP_IFLOW: /* get incoming flow spec. */
			error = sooptcopyout(sopt, &pcb->iflow,
						sizeof(pcb->iflow));
			break;

		case SO_L2CAP_OFLOW: /* get outgoing flow spec. */
			error = sooptcopyout(sopt, &pcb->oflow,
						sizeof(pcb->oflow));
			break;

		case SO_L2CAP_FLUSH: /* get flush timeout */
			error = sooptcopyout(sopt, &pcb->flush_timo,
						sizeof(pcb->flush_timo));
			break;
		case SO_L2CAP_ENCRYPTED: /* get encrypt required */
			error = sooptcopyout(sopt, &pcb->need_encrypt,
						sizeof(pcb->need_encrypt));
			break;


		default:
			error = ENOPROTOOPT;
			break;
		}
		break;

	case SOPT_SET:
		/*
		 * XXX
		 * We do not allow to change these parameters while socket is 
		 * connected or we are in the process of creating a connection.
		 * May be this should indicate re-configuration of the open 
		 * channel?
		 */

		if (pcb->state != NG_BTSOCKET_L2CAP_CLOSED) {
			error = EACCES;
			break;
		}

		switch (sopt->sopt_name) {
		case SO_L2CAP_IMTU: /* set incoming MTU */
			error = sooptcopyin(sopt, &v, sizeof(v), sizeof(v.mtu));
			if (error == 0)
				pcb->imtu = v.mtu;
			break;

		case SO_L2CAP_OFLOW: /* set outgoing flow spec. */
			error = sooptcopyin(sopt, &v, sizeof(v),sizeof(v.flow));
			if (error == 0)
				bcopy(&v.flow, &pcb->oflow, sizeof(pcb->oflow));
			break;

		case SO_L2CAP_FLUSH: /* set flush timeout */
			error = sooptcopyin(sopt, &v, sizeof(v),
						sizeof(v.flush_timo));
			if (error == 0)
				pcb->flush_timo = v.flush_timo;
			break;
		case SO_L2CAP_ENCRYPTED: /*set connect encryption opt*/
			if((pcb->state != NG_BTSOCKET_L2CAP_OPEN) &&
			   (pcb->state != NG_BTSOCKET_L2CAP_W4_ENC_CHANGE)){
				error = sooptcopyin(sopt, &v, sizeof(v),
						    sizeof(v.encryption));
				if(error == 0)
					pcb->need_encrypt = (v.encryption)?1:0;
			}else{
				error = EINVAL;
			}
			break;
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