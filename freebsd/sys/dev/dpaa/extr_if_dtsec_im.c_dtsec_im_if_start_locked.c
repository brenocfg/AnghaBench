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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct mbuf {int dummy; } ;
struct dtsec_softc {int /*<<< orphan*/  sc_txph; TYPE_2__* sc_ifnet; TYPE_1__* sc_mii; } ;
struct TYPE_4__ {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;
struct TYPE_3__ {int mii_media_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTSEC_LOCK_ASSERT (struct dtsec_softc*) ; 
 int E_OK ; 
 int FM_PORT_ImTx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int IFF_DRV_RUNNING ; 
 int IFM_ACTIVE ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  XX_FreeSmart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * XX_MallocSmart (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  m_length (struct mbuf*,int /*<<< orphan*/ *) ; 

void
dtsec_im_if_start_locked(struct dtsec_softc *sc)
{
	uint8_t *buffer;
	uint16_t length;
	struct mbuf *m;
	int error;

	DTSEC_LOCK_ASSERT(sc);
	/* TODO: IFF_DRV_OACTIVE */

	if ((sc->sc_mii->mii_media_status & IFM_ACTIVE) == 0)
		return;

	if ((sc->sc_ifnet->if_drv_flags & IFF_DRV_RUNNING) != IFF_DRV_RUNNING)
		return;

	while (!IFQ_DRV_IS_EMPTY(&sc->sc_ifnet->if_snd)) {
		IFQ_DRV_DEQUEUE(&sc->sc_ifnet->if_snd, m);
		if (m == NULL)
			break;

		length = m_length(m, NULL);
		buffer = XX_MallocSmart(length, 0, sizeof(void *));
		if (!buffer) {
			m_freem(m);
			break;
		}

		m_copydata(m, 0, length, buffer);
		m_freem(m);

		error = FM_PORT_ImTx(sc->sc_txph, buffer, length, TRUE, buffer);
		if (error != E_OK) {
			/* TODO: Ring full */
			XX_FreeSmart(buffer);
			break;
		}
	}
}