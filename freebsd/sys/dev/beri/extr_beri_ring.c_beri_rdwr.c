#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int uint16_t ;
struct uio {int uio_resid; scalar_t__ uio_rw; } ;
struct cdev {struct beri_softc* si_drv1; } ;
struct beri_softc {int data_size; scalar_t__ bsh; scalar_t__ data_read; scalar_t__ data_write; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int in; int out; } ;
typedef  TYPE_1__ control_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__ get_control_reg (struct beri_softc*,int) ; 
 int get_stock (struct beri_softc*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  set_control_reg (struct beri_softc*,int,TYPE_1__*) ; 
 int /*<<< orphan*/  uiomove (int /*<<< orphan*/ *,int,struct uio*) ; 

__attribute__((used)) static int
beri_rdwr(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct beri_softc *sc;
	uint32_t offset;
	control_reg_t c;
	uint16_t *ptr;
	uint8_t *dst;
	int stock;
	int dir;
	int amount;
	int count;

	sc = dev->si_drv1;

	dir = uio->uio_rw ? 1 : 0;

	c = get_control_reg(sc, dir);
	stock = get_stock(sc, dir, &c);
	if (stock < uio->uio_resid) {
		device_printf(sc->dev, "Err: no data/space available\n");
		return (1);
	}

	amount = uio->uio_resid;
	ptr = dir ? &c.in : &c.out;
	count = (sc->data_size - *ptr);

	offset = dir ? sc->data_write : sc->data_read;
	dst = (uint8_t *)(sc->bsh + offset);

	if (amount <= count) {
		uiomove(dst + *ptr, amount, uio);
	} else {
		uiomove(dst + *ptr, count, uio);
		uiomove(dst, (amount - count), uio);
	}

	*ptr = (*ptr + amount) % sc->data_size;
	set_control_reg(sc, dir, &c);

	return (0);
}