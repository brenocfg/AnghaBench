#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wtap_medium {scalar_t__ open; int /*<<< orphan*/  md_mtx; TYPE_1__* tx_handler; int /*<<< orphan*/  md_pktbuf; } ;
struct packet {int id; struct mbuf* m; } ;
struct mbuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  proc; int /*<<< orphan*/  tq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWTAP_PRINTF (char*,int,struct mbuf*) ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  M_WTAP_PACKET ; 
 int M_ZERO ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct packet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 
 scalar_t__ malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pf_list ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
medium_transmit(struct wtap_medium *md, int id, struct mbuf*m)
{

	mtx_lock(&md->md_mtx);
	if (md->open == 0){
		DWTAP_PRINTF("[%d] dropping m=%p\n", id, m);
		m_free(m);
		mtx_unlock(&md->md_mtx);
		return 0;
	}

	DWTAP_PRINTF("[%d] transmiting m=%p\n", id, m);
	struct packet *p = (struct packet *)malloc(sizeof(struct packet),
	    M_WTAP_PACKET, M_ZERO | M_NOWAIT);
	p->id = id;
	p->m = m;

	STAILQ_INSERT_TAIL(&md->md_pktbuf, p, pf_list);
	taskqueue_enqueue(md->tx_handler->tq, &md->tx_handler->proc);
	mtx_unlock(&md->md_mtx);

      return 0;
}