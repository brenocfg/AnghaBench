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
typedef  int /*<<< orphan*/  t_Error ;
struct dtsec_softc {int /*<<< orphan*/  sc_rx_zone; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static t_Error
dtsec_rm_pool_rx_put_buffer(t_Handle h_BufferPool, uint8_t *buffer,
    t_Handle context)
{
	struct dtsec_softc *sc;

	sc = h_BufferPool;
	uma_zfree(sc->sc_rx_zone, buffer);

	return (E_OK);
}