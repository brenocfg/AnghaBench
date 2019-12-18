#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int vi_width; int vi_height; } ;
struct TYPE_12__ {TYPE_2__ va_info; } ;
typedef  TYPE_3__ video_adapter_t ;
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_13__ {int xsize; int ysize; int /*<<< orphan*/  vtb; TYPE_1__* sc; } ;
typedef  TYPE_4__ scr_stat ;
struct TYPE_10__ {TYPE_3__* adp; } ;

/* Variables and functions */
 int sc_vtb_geta (int /*<<< orphan*/ *,int) ; 
 int sc_vtb_getc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sc_vtb_pointer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vidd_clear (TYPE_3__*,int) ; 
 int /*<<< orphan*/  vidd_copy (TYPE_3__*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vidd_putc (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  vidd_puts (TYPE_3__*,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
gfb_draw(scr_stat *scp, int from, int count, int flip)
{
	int c;
	int a;
	int i, n;
	video_adapter_t *adp;

	adp = scp->sc->adp;

	/*
	   Determine if we need to scroll based on the offset
	   and the number of characters to be displayed...
	 */
	if (from + count > scp->xsize*scp->ysize) {

		/*
		   Calculate the number of characters past the end of the
		   visible screen...
		*/
		count = (from + count) -
		    (adp->va_info.vi_width * adp->va_info.vi_height);

		/*
		   Calculate the number of rows past the end of the visible
		   screen...
		*/
		n = (count / adp->va_info.vi_width) + 1;

		/* Scroll to make room for new text rows... */
		vidd_copy(adp, n, 0, n);
#if 0
		vidd_clear(adp, n);
#endif

		/* Display new text rows... */
		vidd_puts(adp, from,
		    (u_int16_t *)sc_vtb_pointer(&scp->vtb, from), count);
	}

	/*
	   We don't need to scroll, so we can just put the characters
	   all-at-once...
	*/
	else {

		/*
		   Determine the method by which we are to display characters
		   (are we going to print forwards or backwards?
		   do we need to do a character-by-character copy, then?)...
		*/
		if (flip)
			for (i = count; i-- > 0; ++from) {
				c = sc_vtb_getc(&scp->vtb, from);
				a = sc_vtb_geta(&scp->vtb, from) >> 8;
				vidd_putc(adp, from, c,
				    (a >> 4) | ((a & 0xf) << 4));
			}
		else {
			vidd_puts(adp, from,
			    (u_int16_t *)sc_vtb_pointer(&scp->vtb, from),
			    count);
		}
	}
}