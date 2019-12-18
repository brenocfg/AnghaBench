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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  struct dtsec_softc* t_Handle ;
struct dtsec_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_PORT_BUFFER_SIZE ; 
 int /*<<< orphan*/ * XX_MallocSmart (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static uint8_t *
dtsec_im_fm_port_rx_get_buf(t_Handle buffer_pool, t_Handle *buf_context_handle)
{
	struct dtsec_softc *sc;
	uint8_t *buffer;

	sc = buffer_pool;

	buffer = XX_MallocSmart(FM_PORT_BUFFER_SIZE, 0, sizeof(void *));
	if (!buffer)
		device_printf(sc->sc_dev, "couldn't allocate RX buffer.\n");

	return (buffer);
}