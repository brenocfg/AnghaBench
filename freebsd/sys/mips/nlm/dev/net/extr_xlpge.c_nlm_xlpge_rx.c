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
typedef  scalar_t__ vm_paddr_t ;
typedef  void* vm_offset_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct nlm_xlpge_softc {int prepad_size; scalar_t__ prepad_en; struct ifnet* xlpge_if; } ;
struct TYPE_2__ {int len; struct ifnet* rcvif; } ;
struct mbuf {int m_data; int m_len; TYPE_1__ m_pkthdr; } ;
struct ifnet {int /*<<< orphan*/  (* if_input ) (struct ifnet*,struct mbuf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 scalar_t__ NAE_CACHELINE_SIZE ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int nlm_cpuid () ; 
 void* nlm_paddr_ld (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  stub2 (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  xlpge_tx (struct ifnet*,struct mbuf*) ; 

__attribute__((used)) static void
nlm_xlpge_rx(struct nlm_xlpge_softc *sc, int port, vm_paddr_t paddr, int len)
{
	struct ifnet	*ifp;
	struct mbuf	*m;
	vm_offset_t	temp;
	unsigned long	mag;
	int		prepad_size;

	ifp = sc->xlpge_if;
	temp = nlm_paddr_ld(paddr - NAE_CACHELINE_SIZE);
	mag = nlm_paddr_ld(paddr - NAE_CACHELINE_SIZE + sizeof(uint64_t));

	m = (struct mbuf *)(intptr_t)temp;
	if (mag != 0xf00bad) {
		/* somebody else packet Error - FIXME in intialization */
		printf("cpu %d: ERR Rx packet paddr %jx, temp %p, mag %lx\n",
		    nlm_cpuid(), (uintmax_t)paddr, (void *)temp, mag);
		return;
	}

	m->m_pkthdr.rcvif = ifp;

#ifdef DUMP_PACKET
	{
		int     i = 0, j = 64;
		unsigned char *buf = (char *)m->m_data;
		printf("(cpu_%d: nlge_rx, !RX_COPY) Rx Packet: length=%d\n",
				nlm_cpuid(), len);
		if (len < j)
			j = len;
		if (sc->prepad_en)
			j += ((sc->prepad_size + 1) * 16);
		for (i = 0; i < j; i++) {
			if (i && (i % 16) == 0)
				printf("\n");
			printf("%02x ", buf[i]);
		}
		printf("\n");
	}
#endif

	if (sc->prepad_en) {
		prepad_size = ((sc->prepad_size + 1) * 16);
		m->m_data += prepad_size;
		m->m_pkthdr.len = m->m_len = (len - prepad_size);
	} else
		m->m_pkthdr.len = m->m_len = len;

	if_inc_counter(ifp, IFCOUNTER_IPACKETS, 1);
#ifdef XLP_DRIVER_LOOPBACK
	if (port == 16 || port == 17)
		(*ifp->if_input)(ifp, m);
	else
		xlpge_tx(ifp, m);
#else
	(*ifp->if_input)(ifp, m);
#endif
}