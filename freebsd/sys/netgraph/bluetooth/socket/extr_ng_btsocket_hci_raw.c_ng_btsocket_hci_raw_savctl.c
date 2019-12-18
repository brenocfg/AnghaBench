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
typedef  int /*<<< orphan*/  tv ;
struct timeval {int dummy; } ;
struct mbuf {int m_flags; struct mbuf* m_next; } ;
typedef  TYPE_2__* ng_btsocket_hci_raw_pcb_p ;
typedef  int /*<<< orphan*/  dir ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_5__ {int flags; TYPE_1__* so; int /*<<< orphan*/  pcb_mtx; } ;
struct TYPE_4__ {int so_options; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int M_PROTO1 ; 
 int NG_BTSOCKET_HCI_RAW_DIRECTION ; 
 int /*<<< orphan*/  SCM_HCI_RAW_DIRECTION ; 
 int /*<<< orphan*/  SCM_TIMESTAMP ; 
 int /*<<< orphan*/  SOL_HCI_RAW ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int SO_TIMESTAMP ; 
 int /*<<< orphan*/  microtime (struct timeval*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mbuf* sbcreatecontrol (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ng_btsocket_hci_raw_savctl(ng_btsocket_hci_raw_pcb_p pcb, struct mbuf **ctl,
		struct mbuf *m) 
{
	int		dir;
	struct timeval	tv;

	mtx_assert(&pcb->pcb_mtx, MA_OWNED);

	if (pcb->flags & NG_BTSOCKET_HCI_RAW_DIRECTION) {
		dir = (m->m_flags & M_PROTO1)? 1 : 0;
		*ctl = sbcreatecontrol((caddr_t) &dir, sizeof(dir),
					SCM_HCI_RAW_DIRECTION, SOL_HCI_RAW);
		if (*ctl != NULL)
			ctl = &((*ctl)->m_next);
	}

	if (pcb->so->so_options & SO_TIMESTAMP) {
		microtime(&tv);
		*ctl = sbcreatecontrol((caddr_t) &tv, sizeof(tv),
					SCM_TIMESTAMP, SOL_SOCKET);
		if (*ctl != NULL)
			ctl = &((*ctl)->m_next);
	}
}