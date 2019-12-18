#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* if_shared_ctx_t ;
struct TYPE_3__ {int isc_tx_maxsize; int isc_tx_maxsegsize; int isc_rx_maxsize; int isc_rx_nsegments; int isc_rx_maxsegsize; int isc_nrxqs; int* isc_nrxd_min; int* isc_nrxd_max; int* isc_nrxd_default; int isc_ntxqs; int* isc_ntxd_min; int* isc_ntxd_max; int* isc_ntxd_default; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int powerof2 (int) ; 

__attribute__((used)) static void
_iflib_assert(if_shared_ctx_t sctx)
{
	int i;

	MPASS(sctx->isc_tx_maxsize);
	MPASS(sctx->isc_tx_maxsegsize);

	MPASS(sctx->isc_rx_maxsize);
	MPASS(sctx->isc_rx_nsegments);
	MPASS(sctx->isc_rx_maxsegsize);

	MPASS(sctx->isc_nrxqs >= 1 && sctx->isc_nrxqs <= 8);
	for (i = 0; i < sctx->isc_nrxqs; i++) {
		MPASS(sctx->isc_nrxd_min[i]);
		MPASS(powerof2(sctx->isc_nrxd_min[i]));
		MPASS(sctx->isc_nrxd_max[i]);
		MPASS(powerof2(sctx->isc_nrxd_max[i]));
		MPASS(sctx->isc_nrxd_default[i]);
		MPASS(powerof2(sctx->isc_nrxd_default[i]));
	}

	MPASS(sctx->isc_ntxqs >= 1 && sctx->isc_ntxqs <= 8);
	for (i = 0; i < sctx->isc_ntxqs; i++) {
		MPASS(sctx->isc_ntxd_min[i]);
		MPASS(powerof2(sctx->isc_ntxd_min[i]));
		MPASS(sctx->isc_ntxd_max[i]);
		MPASS(powerof2(sctx->isc_ntxd_max[i]));
		MPASS(sctx->isc_ntxd_default[i]);
		MPASS(powerof2(sctx->isc_ntxd_default[i]));
	}
}