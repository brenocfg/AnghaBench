#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dtsec_softc {int /*<<< orphan*/  sc_dev; int /*<<< orphan*/ * sc_rx_pool; int /*<<< orphan*/  sc_rx_bpid; int /*<<< orphan*/ * sc_rx_zone; int /*<<< orphan*/  sc_rx_zname; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTASSERT (int) ; 
 int /*<<< orphan*/  DTSEC_RM_POOL_RX_HIGH_MARK ; 
 int /*<<< orphan*/  DTSEC_RM_POOL_RX_LOW_MARK ; 
 int /*<<< orphan*/  DTSEC_RM_POOL_RX_MAX_SIZE ; 
 int EIO ; 
 scalar_t__ FM_PORT_BUFFER_SIZE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/ * bman_pool_create (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dtsec_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dtsec_rm_pool_rx_depleted ; 
 int /*<<< orphan*/  dtsec_rm_pool_rx_free (struct dtsec_softc*) ; 
 int /*<<< orphan*/  dtsec_rm_pool_rx_get_buffer ; 
 int /*<<< orphan*/  dtsec_rm_pool_rx_put_buffer ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/ * uma_zcreate (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

int
dtsec_rm_pool_rx_init(struct dtsec_softc *sc)
{

	/* FM_PORT_BUFFER_SIZE must be less than PAGE_SIZE */
	CTASSERT(FM_PORT_BUFFER_SIZE < PAGE_SIZE);

	snprintf(sc->sc_rx_zname, sizeof(sc->sc_rx_zname), "%s: RX Buffers",
	    device_get_nameunit(sc->sc_dev));

	sc->sc_rx_zone = uma_zcreate(sc->sc_rx_zname, FM_PORT_BUFFER_SIZE, NULL,
	    NULL, NULL, NULL, FM_PORT_BUFFER_SIZE - 1, 0);
	if (sc->sc_rx_zone == NULL)
		return (EIO);

	sc->sc_rx_pool = bman_pool_create(&sc->sc_rx_bpid, FM_PORT_BUFFER_SIZE,
	    0, 0, DTSEC_RM_POOL_RX_MAX_SIZE, dtsec_rm_pool_rx_get_buffer,
	    dtsec_rm_pool_rx_put_buffer, DTSEC_RM_POOL_RX_LOW_MARK,
	    DTSEC_RM_POOL_RX_HIGH_MARK, 0, 0, dtsec_rm_pool_rx_depleted, sc, NULL,
	    NULL);
	if (sc->sc_rx_pool == NULL) {
		device_printf(sc->sc_dev, "NULL rx pool  somehow\n");
		dtsec_rm_pool_rx_free(sc);
		return (EIO);
	}

	return (0);
}