#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int port; } ;
struct TYPE_8__ {TYPE_1__ s; } ;
struct oce_nic_rx_cqe_v1 {TYPE_2__ u0; } ;
struct oce_nic_rx_cqe {int dummy; } ;
struct TYPE_9__ {int port_id; scalar_t__ be3_native; } ;
typedef  TYPE_3__* POCE_SOFTC ;

/* Variables and functions */
 scalar_t__ IS_BE (TYPE_3__*) ; 
 scalar_t__ IS_SH (TYPE_3__*) ; 

__attribute__((used)) static int
oce_cqe_portid_valid(POCE_SOFTC sc, struct oce_nic_rx_cqe *cqe)
{
	struct oce_nic_rx_cqe_v1 *cqe_v1;
	int port_id = 0;

	if (sc->be3_native && (IS_BE(sc) || IS_SH(sc))) {
		cqe_v1 = (struct oce_nic_rx_cqe_v1 *)cqe;
		port_id =  cqe_v1->u0.s.port;
		if (sc->port_id != port_id)
			return 0;
	} else
		;/* For BE3 legacy and Lancer this is dummy */
	
	return 1;

}