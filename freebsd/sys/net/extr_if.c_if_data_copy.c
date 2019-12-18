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
struct ifnet {int /*<<< orphan*/  (* if_get_counter ) (struct ifnet*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  if_lastchange; int /*<<< orphan*/  if_epoch; int /*<<< orphan*/  if_hwassist; int /*<<< orphan*/  if_baudrate; int /*<<< orphan*/  if_metric; int /*<<< orphan*/  if_mtu; int /*<<< orphan*/  if_link_state; int /*<<< orphan*/  if_hdrlen; int /*<<< orphan*/  if_addrlen; int /*<<< orphan*/  if_type; } ;
struct if_data {int ifi_datalen; int /*<<< orphan*/  ifi_noproto; int /*<<< orphan*/  ifi_oqdrops; int /*<<< orphan*/  ifi_iqdrops; int /*<<< orphan*/  ifi_omcasts; int /*<<< orphan*/  ifi_imcasts; int /*<<< orphan*/  ifi_obytes; int /*<<< orphan*/  ifi_ibytes; int /*<<< orphan*/  ifi_collisions; int /*<<< orphan*/  ifi_oerrors; int /*<<< orphan*/  ifi_opackets; int /*<<< orphan*/  ifi_ierrors; int /*<<< orphan*/  ifi_ipackets; int /*<<< orphan*/  ifi_lastchange; int /*<<< orphan*/  ifi_epoch; int /*<<< orphan*/  ifi_hwassist; int /*<<< orphan*/  ifi_baudrate; int /*<<< orphan*/  ifi_metric; int /*<<< orphan*/  ifi_mtu; scalar_t__ ifi_vhid; int /*<<< orphan*/  ifi_link_state; int /*<<< orphan*/  ifi_hdrlen; int /*<<< orphan*/  ifi_addrlen; scalar_t__ ifi_physical; int /*<<< orphan*/  ifi_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_IBYTES ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IMCASTS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_IQDROPS ; 
 int /*<<< orphan*/  IFCOUNTER_NOPROTO ; 
 int /*<<< orphan*/  IFCOUNTER_OBYTES ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OMCASTS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_OQDROPS ; 
 int /*<<< orphan*/  stub1 (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (struct ifnet*,int /*<<< orphan*/ ) ; 

void
if_data_copy(struct ifnet *ifp, struct if_data *ifd)
{

	ifd->ifi_type = ifp->if_type;
	ifd->ifi_physical = 0;
	ifd->ifi_addrlen = ifp->if_addrlen;
	ifd->ifi_hdrlen = ifp->if_hdrlen;
	ifd->ifi_link_state = ifp->if_link_state;
	ifd->ifi_vhid = 0;
	ifd->ifi_datalen = sizeof(struct if_data);
	ifd->ifi_mtu = ifp->if_mtu;
	ifd->ifi_metric = ifp->if_metric;
	ifd->ifi_baudrate = ifp->if_baudrate;
	ifd->ifi_hwassist = ifp->if_hwassist;
	ifd->ifi_epoch = ifp->if_epoch;
	ifd->ifi_lastchange = ifp->if_lastchange;

	ifd->ifi_ipackets = ifp->if_get_counter(ifp, IFCOUNTER_IPACKETS);
	ifd->ifi_ierrors = ifp->if_get_counter(ifp, IFCOUNTER_IERRORS);
	ifd->ifi_opackets = ifp->if_get_counter(ifp, IFCOUNTER_OPACKETS);
	ifd->ifi_oerrors = ifp->if_get_counter(ifp, IFCOUNTER_OERRORS);
	ifd->ifi_collisions = ifp->if_get_counter(ifp, IFCOUNTER_COLLISIONS);
	ifd->ifi_ibytes = ifp->if_get_counter(ifp, IFCOUNTER_IBYTES);
	ifd->ifi_obytes = ifp->if_get_counter(ifp, IFCOUNTER_OBYTES);
	ifd->ifi_imcasts = ifp->if_get_counter(ifp, IFCOUNTER_IMCASTS);
	ifd->ifi_omcasts = ifp->if_get_counter(ifp, IFCOUNTER_OMCASTS);
	ifd->ifi_iqdrops = ifp->if_get_counter(ifp, IFCOUNTER_IQDROPS);
	ifd->ifi_oqdrops = ifp->if_get_counter(ifp, IFCOUNTER_OQDROPS);
	ifd->ifi_noproto = ifp->if_get_counter(ifp, IFCOUNTER_NOPROTO);
}