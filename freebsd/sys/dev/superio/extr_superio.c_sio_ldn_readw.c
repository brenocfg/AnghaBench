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
typedef  int /*<<< orphan*/  uint16_t ;
struct siosc {scalar_t__ enable_reg; scalar_t__ current_ldn; int /*<<< orphan*/  io_res; int /*<<< orphan*/  conf_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sio_ldn_select (struct siosc*,scalar_t__) ; 
 int /*<<< orphan*/  sio_readw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static uint16_t
sio_ldn_readw(struct siosc *sc, uint8_t ldn, uint8_t reg)
{
	mtx_assert(&sc->conf_lock, MA_OWNED);
	if (reg >= sc->enable_reg) {
		sio_ldn_select(sc, ldn);
		KASSERT(sc->current_ldn == ldn, ("sio_ldn_select failed"));
	}
	return (sio_readw(sc->io_res, reg));
}