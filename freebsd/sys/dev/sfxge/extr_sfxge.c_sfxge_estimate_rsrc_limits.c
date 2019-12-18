#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct sfxge_softc {unsigned int max_rss_channels; unsigned int evq_max; int /*<<< orphan*/  dev; int /*<<< orphan*/  enp; } ;
typedef  int /*<<< orphan*/  limits ;
struct TYPE_4__ {int edl_min_evq_count; unsigned int edl_max_evq_count; int edl_min_txq_count; unsigned int edl_max_txq_count; int edl_min_rxq_count; unsigned int edl_max_rxq_count; } ;
typedef  TYPE_1__ efx_drv_limits_t ;

/* Variables and functions */
 unsigned int EFX_MAXRSS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAX (unsigned int,int) ; 
 void* MIN (int,unsigned int) ; 
 int SFXGE_EVQ0_N_TXQ (struct sfxge_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  efx_nic_fini (int /*<<< orphan*/ ) ; 
 int efx_nic_get_vi_pool (int /*<<< orphan*/ ,int*,int*,int*) ; 
 int efx_nic_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_nic_set_drv_limits (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int mp_ncpus ; 
 unsigned int rss_getnumbuckets () ; 

__attribute__((used)) static int
sfxge_estimate_rsrc_limits(struct sfxge_softc *sc)
{
	efx_drv_limits_t limits;
	int rc;
	unsigned int evq_max;
	uint32_t evq_allocated;
	uint32_t rxq_allocated;
	uint32_t txq_allocated;

	/*
	 * Limit the number of event queues to:
	 *  - number of CPUs
	 *  - hardwire maximum RSS channels
	 *  - administratively specified maximum RSS channels
	 */
#ifdef RSS
	/*
	 * Avoid extra limitations so that the number of queues
	 * may be configured at administrator's will
	 */
	evq_max = MIN(MAX(rss_getnumbuckets(), 1), EFX_MAXRSS);
#else
	evq_max = MIN(mp_ncpus, EFX_MAXRSS);
#endif
	if (sc->max_rss_channels > 0)
		evq_max = MIN(evq_max, sc->max_rss_channels);

	memset(&limits, 0, sizeof(limits));

	limits.edl_min_evq_count = 1;
	limits.edl_max_evq_count = evq_max;
	limits.edl_min_txq_count = SFXGE_EVQ0_N_TXQ(sc);
	limits.edl_max_txq_count = evq_max + SFXGE_EVQ0_N_TXQ(sc) - 1;
	limits.edl_min_rxq_count = 1;
	limits.edl_max_rxq_count = evq_max;

	efx_nic_set_drv_limits(sc->enp, &limits);

	if ((rc = efx_nic_init(sc->enp)) != 0)
		return (rc);

	rc = efx_nic_get_vi_pool(sc->enp, &evq_allocated, &rxq_allocated,
				 &txq_allocated);
	if (rc != 0) {
		efx_nic_fini(sc->enp);
		return (rc);
	}

	KASSERT(txq_allocated >= SFXGE_EVQ0_N_TXQ(sc),
		("txq_allocated < %u", SFXGE_EVQ0_N_TXQ(sc)));

	sc->evq_max = MIN(evq_allocated, evq_max);
	sc->evq_max = MIN(rxq_allocated, sc->evq_max);
	sc->evq_max = MIN(txq_allocated - (SFXGE_EVQ0_N_TXQ(sc) - 1),
			  sc->evq_max);

	KASSERT(sc->evq_max <= evq_max,
		("allocated more than maximum requested"));

#ifdef RSS
	if (sc->evq_max < rss_getnumbuckets())
		device_printf(sc->dev, "The number of allocated queues (%u) "
			      "is less than the number of RSS buckets (%u); "
			      "performance degradation might be observed",
			      sc->evq_max, rss_getnumbuckets());
#endif

	/*
	 * NIC is kept initialized in the case of success to be able to
	 * initialize port to find out media types.
	 */
	return (0);
}