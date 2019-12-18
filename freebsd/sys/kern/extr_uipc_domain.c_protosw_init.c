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
struct protosw {int /*<<< orphan*/  (* pr_init ) () ;TYPE_1__* pr_domain; struct pr_usrreqs* pr_usrreqs; } ;
struct pr_usrreqs {int /*<<< orphan*/  pru_ready; int /*<<< orphan*/  pru_sopoll; int /*<<< orphan*/  pru_soreceive; int /*<<< orphan*/  pru_sosend; int /*<<< orphan*/  pru_sockaddr; int /*<<< orphan*/  pru_shutdown; int /*<<< orphan*/  pru_sense; int /*<<< orphan*/  pru_rcvoob; int /*<<< orphan*/  pru_rcvd; int /*<<< orphan*/  pru_peeraddr; int /*<<< orphan*/  pru_listen; int /*<<< orphan*/  pru_disconnect; int /*<<< orphan*/  pru_control; int /*<<< orphan*/  pru_connectat; int /*<<< orphan*/  pru_connect2; int /*<<< orphan*/  pru_connect; int /*<<< orphan*/  pru_bindat; int /*<<< orphan*/  pru_bind; int /*<<< orphan*/  pru_aio_queue; int /*<<< orphan*/  pru_accept; int /*<<< orphan*/ * pru_send; int /*<<< orphan*/ * pru_abort; int /*<<< orphan*/ * pru_attach; } ;
struct TYPE_2__ {struct protosw* dom_protosw; int /*<<< orphan*/  dom_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pru_accept_notsupp ; 
 int /*<<< orphan*/  pru_aio_queue_notsupp ; 
 int /*<<< orphan*/  pru_bind_notsupp ; 
 int /*<<< orphan*/  pru_bindat_notsupp ; 
 int /*<<< orphan*/  pru_connect2_notsupp ; 
 int /*<<< orphan*/  pru_connect_notsupp ; 
 int /*<<< orphan*/  pru_connectat_notsupp ; 
 int /*<<< orphan*/  pru_control_notsupp ; 
 int /*<<< orphan*/  pru_disconnect_notsupp ; 
 int /*<<< orphan*/  pru_listen_notsupp ; 
 int /*<<< orphan*/  pru_peeraddr_notsupp ; 
 int /*<<< orphan*/  pru_rcvd_notsupp ; 
 int /*<<< orphan*/  pru_rcvoob_notsupp ; 
 int /*<<< orphan*/  pru_ready_notsupp ; 
 int /*<<< orphan*/  pru_sense_null ; 
 int /*<<< orphan*/  pru_shutdown_notsupp ; 
 int /*<<< orphan*/  pru_sockaddr_notsupp ; 
 int /*<<< orphan*/  sopoll_generic ; 
 int /*<<< orphan*/  soreceive_generic ; 
 int /*<<< orphan*/  sosend_generic ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void
protosw_init(struct protosw *pr)
{
	struct pr_usrreqs *pu;

	pu = pr->pr_usrreqs;
	KASSERT(pu != NULL, ("protosw_init: %ssw[%d] has no usrreqs!",
	    pr->pr_domain->dom_name,
	    (int)(pr - pr->pr_domain->dom_protosw)));

	/*
	 * Protocol switch methods fall into three categories: mandatory,
	 * mandatory but protosw_init() provides a default, and optional.
	 *
	 * For true protocols (i.e., pru_attach != NULL), KASSERT truly
	 * mandatory methods with no defaults, and initialize defaults for
	 * other mandatory methods if the protocol hasn't defined an
	 * implementation (NULL function pointer).
	 */
#if 0
	if (pu->pru_attach != NULL) {
		KASSERT(pu->pru_abort != NULL,
		    ("protosw_init: %ssw[%d] pru_abort NULL",
		    pr->pr_domain->dom_name,
		    (int)(pr - pr->pr_domain->dom_protosw)));
		KASSERT(pu->pru_send != NULL,
		    ("protosw_init: %ssw[%d] pru_send NULL",
		    pr->pr_domain->dom_name,
		    (int)(pr - pr->pr_domain->dom_protosw)));
	}
#endif

#define DEFAULT(foo, bar)	if ((foo) == NULL)  (foo) = (bar)
	DEFAULT(pu->pru_accept, pru_accept_notsupp);
	DEFAULT(pu->pru_aio_queue, pru_aio_queue_notsupp);
	DEFAULT(pu->pru_bind, pru_bind_notsupp);
	DEFAULT(pu->pru_bindat, pru_bindat_notsupp);
	DEFAULT(pu->pru_connect, pru_connect_notsupp);
	DEFAULT(pu->pru_connect2, pru_connect2_notsupp);
	DEFAULT(pu->pru_connectat, pru_connectat_notsupp);
	DEFAULT(pu->pru_control, pru_control_notsupp);
	DEFAULT(pu->pru_disconnect, pru_disconnect_notsupp);
	DEFAULT(pu->pru_listen, pru_listen_notsupp);
	DEFAULT(pu->pru_peeraddr, pru_peeraddr_notsupp);
	DEFAULT(pu->pru_rcvd, pru_rcvd_notsupp);
	DEFAULT(pu->pru_rcvoob, pru_rcvoob_notsupp);
	DEFAULT(pu->pru_sense, pru_sense_null);
	DEFAULT(pu->pru_shutdown, pru_shutdown_notsupp);
	DEFAULT(pu->pru_sockaddr, pru_sockaddr_notsupp);
	DEFAULT(pu->pru_sosend, sosend_generic);
	DEFAULT(pu->pru_soreceive, soreceive_generic);
	DEFAULT(pu->pru_sopoll, sopoll_generic);
	DEFAULT(pu->pru_ready, pru_ready_notsupp);
#undef DEFAULT
	if (pr->pr_init)
		(*pr->pr_init)();
}