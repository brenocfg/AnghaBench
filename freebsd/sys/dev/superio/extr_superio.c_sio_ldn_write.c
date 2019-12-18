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
struct siosc {scalar_t__ ldn_reg; scalar_t__ current_ldn; int /*<<< orphan*/  io_res; int /*<<< orphan*/  conf_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  sio_ldn_select (struct siosc*,scalar_t__) ; 
 int /*<<< orphan*/  sio_write (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
sio_ldn_write(struct siosc *sc, uint8_t ldn, uint8_t reg, uint8_t val)
{
	mtx_assert(&sc->conf_lock, MA_OWNED);
	if (reg <= sc->ldn_reg) {
		printf("ignored attempt to write special register 0x%x\n", reg);
		return;
	}
	sio_ldn_select(sc, ldn);
	KASSERT(sc->current_ldn == ldn, ("sio_ldn_select failed"));
	sio_write(sc->io_res, reg, val);
}