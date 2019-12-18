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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  struct dtsec_softc* t_Handle ;
struct mbuf {int dummy; } ;
struct dtsec_softc {TYPE_1__* sc_ifnet; } ;
typedef  int /*<<< orphan*/  e_RxStoreResponse ;
struct TYPE_3__ {int /*<<< orphan*/  (* if_input ) (TYPE_1__*,struct mbuf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  XX_FreeSmart (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_RX_STORE_RESPONSE_CONTINUE ; 
 struct mbuf* m_devget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,struct mbuf*) ; 

__attribute__((used)) static e_RxStoreResponse
dtsec_im_fm_port_rx_callback(t_Handle app, uint8_t *data, uint16_t length,
    uint16_t status, uint8_t position, t_Handle buf_context)
{
	struct dtsec_softc *sc;
	struct mbuf *m;

	/* TODO STATUS / Position checking */
	sc = app;

	m = m_devget(data, length, 0, sc->sc_ifnet, NULL);
	if (m)
		(*sc->sc_ifnet->if_input)(sc->sc_ifnet, m);

	XX_FreeSmart(data);

	return (e_RX_STORE_RESPONSE_CONTINUE);
}