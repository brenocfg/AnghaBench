#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct mbx_get_pport_stats {int dummy; } ;
struct mbx_get_nic_stats_v2 {int dummy; } ;
struct mbx_get_nic_stats_v1 {int dummy; } ;
struct mbx_get_nic_stats_v0 {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  stats_mem; } ;
typedef  TYPE_1__* POCE_SOFTC ;

/* Variables and functions */
 scalar_t__ IS_BE2 (TYPE_1__*) ; 
 scalar_t__ IS_BE3 (TYPE_1__*) ; 
 scalar_t__ IS_SH (TYPE_1__*) ; 
 scalar_t__ IS_XE201 (TYPE_1__*) ; 
 int oce_dma_alloc (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
oce_stats_init(POCE_SOFTC sc)
{
	int rc = 0, sz = 0;


        if( IS_BE2(sc) ) 
		sz = sizeof(struct mbx_get_nic_stats_v0);
        else if( IS_BE3(sc) ) 
		sz = sizeof(struct mbx_get_nic_stats_v1);
        else if( IS_SH(sc)) 
		sz = sizeof(struct mbx_get_nic_stats_v2);
        else if( IS_XE201(sc) )
		sz = sizeof(struct mbx_get_pport_stats);

	rc = oce_dma_alloc(sc, sz, &sc->stats_mem, 0);

	return rc;
}