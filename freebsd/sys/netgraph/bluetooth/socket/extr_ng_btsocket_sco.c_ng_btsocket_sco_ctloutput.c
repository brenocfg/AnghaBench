#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct sockopt {scalar_t__ sopt_level; int sopt_dir; int /*<<< orphan*/  sopt_name; } ;
struct socket {int dummy; } ;
typedef  TYPE_2__* ng_btsocket_sco_pcb_p ;
struct TYPE_5__ {int con_handle; int /*<<< orphan*/  pcb_mtx; TYPE_1__* rt; int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int pkt_size; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOPROTOOPT ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  NG_BTSOCKET_SCO_OPEN ; 
 scalar_t__ SOL_SCO ; 
#define  SOPT_GET 131 
#define  SOPT_SET 130 
#define  SO_SCO_CONNINFO 129 
#define  SO_SCO_MTU 128 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ng_btsocket_sco_node ; 
 TYPE_2__* so2sco_pcb (struct socket*) ; 
 int sooptcopyout (struct sockopt*,int*,int) ; 

int
ng_btsocket_sco_ctloutput(struct socket *so, struct sockopt *sopt)
{
	ng_btsocket_sco_pcb_p	pcb = so2sco_pcb(so);
        int			error, tmp;

	if (ng_btsocket_sco_node == NULL) 
		return (EINVAL);
	if (pcb == NULL)
		return (EINVAL);

	if (sopt->sopt_level != SOL_SCO)
		return (0);

	mtx_lock(&pcb->pcb_mtx);

	switch (sopt->sopt_dir) {
	case SOPT_GET:
		if (pcb->state != NG_BTSOCKET_SCO_OPEN) {
			error = ENOTCONN;
			break;
		}
		
		switch (sopt->sopt_name) {
		case SO_SCO_MTU:
			tmp = pcb->rt->pkt_size;
			error = sooptcopyout(sopt, &tmp, sizeof(tmp));
			break;

		case SO_SCO_CONNINFO:
			tmp = pcb->con_handle;
			error = sooptcopyout(sopt, &tmp, sizeof(tmp));
			break;

		default:
			error = EINVAL;
			break;
		}
		break;

	case SOPT_SET:
		error = ENOPROTOOPT;
		break;

	default:
		error = EINVAL;
		break;
	}

	mtx_unlock(&pcb->pcb_mtx);
	
	return (error);
}