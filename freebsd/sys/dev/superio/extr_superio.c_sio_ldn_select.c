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
typedef  scalar_t__ uint8_t ;
struct siosc {scalar_t__ current_ldn; int /*<<< orphan*/  ldn_reg; int /*<<< orphan*/  io_res; int /*<<< orphan*/  conf_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
sio_ldn_select(struct siosc *sc, uint8_t ldn)
{
	mtx_assert(&sc->conf_lock, MA_OWNED);
	if (ldn == sc->current_ldn)
		return;
	sio_write(sc->io_res, sc->ldn_reg, ldn);
	sc->current_ldn = ldn;
}