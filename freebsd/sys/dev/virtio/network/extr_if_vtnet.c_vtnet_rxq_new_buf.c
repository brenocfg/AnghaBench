#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vtnet_softc {int /*<<< orphan*/  vtnet_rx_nmbufs; } ;
struct vtnet_rxq {struct vtnet_softc* vtnrx_sc; } ;
struct mbuf {int dummy; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* vtnet_rx_alloc_buf (struct vtnet_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int vtnet_rxq_enqueue_buf (struct vtnet_rxq*,struct mbuf*) ; 

__attribute__((used)) static int
vtnet_rxq_new_buf(struct vtnet_rxq *rxq)
{
	struct vtnet_softc *sc;
	struct mbuf *m;
	int error;

	sc = rxq->vtnrx_sc;

	m = vtnet_rx_alloc_buf(sc, sc->vtnet_rx_nmbufs, NULL);
	if (m == NULL)
		return (ENOBUFS);

	error = vtnet_rxq_enqueue_buf(rxq, m);
	if (error)
		m_freem(m);

	return (error);
}