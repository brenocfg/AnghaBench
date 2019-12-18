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
struct dtsec_softc {int /*<<< orphan*/  sc_rx_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/ * uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint8_t *
dtsec_rm_pool_rx_get_buffer(t_Handle h_BufferPool, t_Handle *context)
{
	struct dtsec_softc *sc;
	uint8_t *buffer;

	sc = h_BufferPool;
	buffer = uma_zalloc(sc->sc_rx_zone, M_NOWAIT);

	return (buffer);
}