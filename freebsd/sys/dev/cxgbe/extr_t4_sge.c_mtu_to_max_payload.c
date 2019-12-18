#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fl_pktshift; } ;
struct TYPE_4__ {TYPE_1__ sge; } ;
struct adapter {TYPE_2__ params; } ;

/* Variables and functions */
 int ETHER_HDR_LEN ; 
 int ETHER_VLAN_ENCAP_LEN ; 

__attribute__((used)) static inline int
mtu_to_max_payload(struct adapter *sc, int mtu)
{

	/* large enough even when hw VLAN extraction is disabled */
	return (sc->params.sge.fl_pktshift + ETHER_HDR_LEN +
	    ETHER_VLAN_ENCAP_LEN + mtu);
}