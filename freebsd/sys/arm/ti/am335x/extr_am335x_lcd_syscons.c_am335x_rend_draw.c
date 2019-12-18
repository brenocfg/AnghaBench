#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  video_adapter_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {int /*<<< orphan*/  vtb; TYPE_1__* sc; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_4__ {int /*<<< orphan*/ * adp; } ;

/* Variables and functions */
 int sc_vtb_geta (int /*<<< orphan*/ *,int) ; 
 int sc_vtb_getc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sc_vtb_pointer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vidd_putc (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  vidd_puts (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
am335x_rend_draw(scr_stat* scp, int from, int count, int flip)
{
	video_adapter_t* adp = scp->sc->adp;
	int i, c, a;

	if (!flip) {
		/* Normal printing */
		vidd_puts(adp, from, (uint16_t*)sc_vtb_pointer(&scp->vtb, from), count);
	} else {	
		/* This is for selections and such: invert the color attribute */
		for (i = count; i-- > 0; ++from) {
			c = sc_vtb_getc(&scp->vtb, from);
			a = sc_vtb_geta(&scp->vtb, from) >> 8;
			vidd_putc(adp, from, c, (a >> 4) | ((a & 0xf) << 4));
		}
	}
}