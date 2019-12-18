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
typedef  int /*<<< orphan*/  uint16_t ;
struct udphdr {scalar_t__ uh_ulen; int /*<<< orphan*/  uh_sum; void* uh_sport; void* uh_dport; } ;
struct gre_softc {int gre_options; int /*<<< orphan*/  gre_port; } ;

/* Variables and functions */
 int GRE_UDPENCAP ; 
 int /*<<< orphan*/  GRE_UDPPORT ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  gre_ioctl_sx ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
gre_update_udphdr(struct gre_softc *sc, struct udphdr *udp, uint16_t csum)
{

	sx_assert(&gre_ioctl_sx, SA_XLOCKED);
	MPASS(sc->gre_options & GRE_UDPENCAP);

	udp->uh_dport = htons(GRE_UDPPORT);
	udp->uh_sport = htons(sc->gre_port);
	udp->uh_sum = csum;
	udp->uh_ulen = 0;
}