#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct octm_softc {int /*<<< orphan*/  sc_port; TYPE_4__* sc_ifp; int /*<<< orphan*/  sc_dev; } ;
struct TYPE_7__ {int len; TYPE_4__* rcvif; } ;
struct mbuf {int m_len; TYPE_2__ m_pkthdr; int /*<<< orphan*/  m_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  irthresh; } ;
struct TYPE_8__ {int /*<<< orphan*/  u64; TYPE_1__ s; } ;
typedef  TYPE_3__ cvmx_mixx_isr_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* if_input ) (TYPE_4__*,struct mbuf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MIXX_ISR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  MCLBYTES ; 
 int /*<<< orphan*/  MT_DATA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_PKTHDR ; 
 int cvmx_mgmt_port_receive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  if_inc_counter (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct mbuf* m_getcl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,struct mbuf*) ; 

__attribute__((used)) static void
octm_rx_intr(void *arg)
{
	struct octm_softc *sc = arg;
	cvmx_mixx_isr_t mixx_isr;
	int len;

	mixx_isr.u64 = cvmx_read_csr(CVMX_MIXX_ISR(sc->sc_port));
	if (!mixx_isr.s.irthresh) {
		device_printf(sc->sc_dev, "stray interrupt.\n");
		return;
	}

	for (;;) {
		struct mbuf *m = m_getcl(M_NOWAIT, MT_DATA, M_PKTHDR);
		if (m == NULL) {
			device_printf(sc->sc_dev, "no memory for receive mbuf.\n");
			return;
		}


		len = cvmx_mgmt_port_receive(sc->sc_port, MCLBYTES, m->m_data);
		if (len > 0) {
			m->m_pkthdr.rcvif = sc->sc_ifp;
			m->m_pkthdr.len = m->m_len = len;

			if_inc_counter(sc->sc_ifp, IFCOUNTER_IPACKETS, 1);

			(*sc->sc_ifp->if_input)(sc->sc_ifp, m);

			continue;
		}

		m_freem(m);

		if (len == 0)
			break;

		if_inc_counter(sc->sc_ifp, IFCOUNTER_IERRORS, 1);
	}

	/* Acknowledge interrupts.  */
	cvmx_write_csr(CVMX_MIXX_ISR(sc->sc_port), mixx_isr.u64);
	cvmx_read_csr(CVMX_MIXX_ISR(sc->sc_port));
}