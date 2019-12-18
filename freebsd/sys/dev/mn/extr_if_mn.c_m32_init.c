#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mn_softc {TYPE_1__* m32x; } ;
struct TYPE_2__ {int conf; int mode1; int mode2; int txpoll; int lconf; int imask; } ;

/* Variables and functions */

__attribute__((used)) static void
m32_init(struct mn_softc *sc)
{

	sc->m32x->conf =  0x00000000;
	sc->m32x->mode1 = 0x81048000 + 1600; 	/* XXX: temp */
#if 1
	sc->m32x->mode2 = 0x00000081;
	sc->m32x->txpoll = 0xffffffff;
#elif 1
	sc->m32x->mode2 = 0x00000081;
	sc->m32x->txpoll = 0xffffffff;
#else
	sc->m32x->mode2 = 0x00000101;
#endif
	sc->m32x->lconf = 0x6060009B;
	sc->m32x->imask = 0x00000000;
}