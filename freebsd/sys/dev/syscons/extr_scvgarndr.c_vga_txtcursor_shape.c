#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int font_size; TYPE_1__* sc; } ;
typedef  TYPE_2__ scr_stat ;
struct TYPE_5__ {int /*<<< orphan*/  adp; } ;

/* Variables and functions */
 int /*<<< orphan*/  vga_setmdp (TYPE_2__*) ; 
 int /*<<< orphan*/  vidd_set_hw_cursor_shape (int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void 
vga_txtcursor_shape(scr_stat *scp, int base, int height, int blink)
{
	vga_setmdp(scp);
	if (base < 0 || base >= scp->font_size)
		return;
	/* the caller may set height <= 0 in order to disable the cursor */
	vidd_set_hw_cursor_shape(scp->sc->adp, base, height,
	    scp->font_size, blink);
}