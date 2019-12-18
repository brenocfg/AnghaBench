#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
struct TYPE_3__ {int xsize; int ysize; int /*<<< orphan*/  scr; int /*<<< orphan*/  vtb; } ;
typedef  TYPE_1__ scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  sc_vtb_copy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int) ; 
 int sc_vtb_geta (int /*<<< orphan*/ *,int) ; 
 int sc_vtb_getc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sc_vtb_pointer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sc_vtb_putchar (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int vga_flipattr (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vga_txtdraw(scr_stat *scp, int from, int count, int flip)
{
	vm_offset_t p;
	int c;
	int a;

	if (from + count > scp->xsize*scp->ysize)
		count = scp->xsize*scp->ysize - from;

	if (flip) {
		for (p = sc_vtb_pointer(&scp->scr, from); count-- > 0; ++from) {
			c = sc_vtb_getc(&scp->vtb, from);
			a = sc_vtb_geta(&scp->vtb, from);
			a = vga_flipattr(a, TRUE);
			p = sc_vtb_putchar(&scp->scr, p, c, a);
		}
	} else {
		sc_vtb_copy(&scp->vtb, from, &scp->scr, from, count);
	}
}