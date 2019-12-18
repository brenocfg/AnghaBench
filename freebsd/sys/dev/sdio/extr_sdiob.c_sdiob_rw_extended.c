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
typedef  int /*<<< orphan*/  uint32_t ;
struct sdiob_softc {int /*<<< orphan*/  periph; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  cam_periph_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_periph_unlock (int /*<<< orphan*/ ) ; 
 struct sdiob_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int sdiob_rw_extended_sc (struct sdiob_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
sdiob_rw_extended(device_t dev, uint8_t fn, uint32_t addr, bool wr,
    uint32_t size, uint8_t *buffer, bool incaddr)
{
	struct sdiob_softc *sc;
	int error;

	sc = device_get_softc(dev);
	cam_periph_lock(sc->periph);
	error = sdiob_rw_extended_sc(sc, fn, addr, wr, size, buffer, incaddr);
	cam_periph_unlock(sc->periph);
	return (error);
}