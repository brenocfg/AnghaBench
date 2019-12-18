#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct dtsec_softc* ext_arg2; void* ext_arg1; } ;
struct mbuf {TYPE_1__ m_ext; } ;
struct dtsec_softc {int /*<<< orphan*/  sc_rx_pool; } ;

/* Variables and functions */
 scalar_t__ DTSEC_RM_POOL_RX_MAX_SIZE ; 
 scalar_t__ bman_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bman_put_buffer (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dtsec_rm_pool_rx_put_buffer (struct dtsec_softc*,void*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dtsec_rm_fqr_mext_free(struct mbuf *m)
{
	struct dtsec_softc *sc;
	void *buffer;

	buffer = m->m_ext.ext_arg1;
	sc = m->m_ext.ext_arg2;
	if (bman_count(sc->sc_rx_pool) <= DTSEC_RM_POOL_RX_MAX_SIZE)
		bman_put_buffer(sc->sc_rx_pool, buffer);
	else
		dtsec_rm_pool_rx_put_buffer(sc, buffer, NULL);
}