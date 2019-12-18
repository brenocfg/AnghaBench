#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint16_t ;
struct normal_vlan {size_t vtag; } ;
struct TYPE_6__ {int vlans_added; scalar_t__ if_id; scalar_t__* vlan_tag; TYPE_1__* ifp; } ;
struct TYPE_5__ {int if_capenable; } ;
typedef  TYPE_2__* POCE_SOFTC ;

/* Variables and functions */
 int IFCAP_VLAN_HWFILTER ; 
 int MAX_VLANFILTER_SIZE ; 
 size_t MAX_VLANS ; 
 int oce_config_vlan (TYPE_2__*,int /*<<< orphan*/ ,struct normal_vlan*,size_t,int,int) ; 

__attribute__((used)) static int
oce_vid_config(POCE_SOFTC sc)
{
	struct normal_vlan vtags[MAX_VLANFILTER_SIZE];
	uint16_t ntags = 0, i;
	int status = 0;

	if ((sc->vlans_added <= MAX_VLANFILTER_SIZE) && 
			(sc->ifp->if_capenable & IFCAP_VLAN_HWFILTER)) {
		for (i = 0; i < MAX_VLANS; i++) {
			if (sc->vlan_tag[i]) {
				vtags[ntags].vtag = i;
				ntags++;
			}
		}
		if (ntags)
			status = oce_config_vlan(sc, (uint8_t) sc->if_id,
						vtags, ntags, 1, 0); 
	} else 
		status = oce_config_vlan(sc, (uint8_t) sc->if_id,
					 	NULL, 0, 1, 1);
	return status;
}