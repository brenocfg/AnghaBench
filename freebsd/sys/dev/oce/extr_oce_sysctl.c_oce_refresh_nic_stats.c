#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  stats_mem; } ;
typedef  TYPE_1__* POCE_SOFTC ;

/* Variables and functions */
 scalar_t__ IS_BE2 (TYPE_1__*) ; 
 scalar_t__ IS_BE3 (TYPE_1__*) ; 
 scalar_t__ IS_SH (TYPE_1__*) ; 
 scalar_t__ IS_XE201 (TYPE_1__*) ; 
 int /*<<< orphan*/  copy_stats_to_sc_be2 (TYPE_1__*) ; 
 int /*<<< orphan*/  copy_stats_to_sc_be3 (TYPE_1__*) ; 
 int /*<<< orphan*/  copy_stats_to_sc_sh (TYPE_1__*) ; 
 int /*<<< orphan*/  copy_stats_to_sc_xe201 (TYPE_1__*) ; 
 int oce_mbox_get_nic_stats_v0 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int oce_mbox_get_nic_stats_v1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int oce_mbox_get_nic_stats_v2 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int oce_mbox_get_pport_stats (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

int
oce_refresh_nic_stats(POCE_SOFTC sc)
{
	int rc = 0, reset = 0;

	if( IS_BE2(sc) ) {
		rc = oce_mbox_get_nic_stats_v0(sc, &sc->stats_mem);
		if (!rc)
			copy_stats_to_sc_be2(sc);
	}else if( IS_BE3(sc) ) {
		rc = oce_mbox_get_nic_stats_v1(sc, &sc->stats_mem);
		if (!rc)
			copy_stats_to_sc_be3(sc);
	}else if( IS_SH(sc)) {
		rc = oce_mbox_get_nic_stats_v2(sc, &sc->stats_mem);
		if (!rc)
			copy_stats_to_sc_sh(sc);
	}else if( IS_XE201(sc) ){
		rc = oce_mbox_get_pport_stats(sc, &sc->stats_mem, reset);
		if (!rc)
			copy_stats_to_sc_xe201(sc);
	}

	return rc;
}