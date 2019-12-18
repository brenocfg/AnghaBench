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
struct knote {int kn_data; struct beri_softc* kn_hook; } ;
struct beri_softc {int dummy; } ;
struct TYPE_5__ {int interrupt_level; int /*<<< orphan*/  cdes; } ;
typedef  TYPE_1__ control_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  CDES_INT_EN ; 
 TYPE_1__ get_control_reg (struct beri_softc*,int /*<<< orphan*/ ) ; 
 int get_stock (struct beri_softc*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  set_control_reg (struct beri_softc*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int
beri_kqread(struct knote *kn, long hint)
{
	struct beri_softc *sc;
	control_reg_t c;
	int stock;

	sc = kn->kn_hook;

	c = get_control_reg(sc, 0);
	stock = get_stock(sc, 0, &c);
	if (stock) {
		kn->kn_data = stock;
		return (1);
	}

	kn->kn_data = 0;

	/* Wait at least one new byte in buffer */
	c.interrupt_level = 1;

	/* Enable interrupts */
	c.cdes |= (CDES_INT_EN);
	set_control_reg(sc, 0, &c);

	return (0);
}