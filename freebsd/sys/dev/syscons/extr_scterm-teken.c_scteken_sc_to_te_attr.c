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
struct TYPE_3__ {unsigned char ta_fgcolor; unsigned char ta_bgcolor; scalar_t__ ta_format; } ;
typedef  TYPE_1__ teken_attr_t ;

/* Variables and functions */
 unsigned char* sc_to_te_color ; 

__attribute__((used)) static void
scteken_sc_to_te_attr(unsigned char color, teken_attr_t *a)
{

	/*
	 * Conversions of attrs are not reversible.  Since sc attrs are
	 * pure colors in the simplest mode (16-color graphics) and the
	 * API is too deficient to tell us the mode, always convert to
	 * pure colors.  The conversion is essentially the identity except
	 * for reordering the non-brightness bits in the 2 color numbers.
	 */
	a->ta_format = 0;
	a->ta_fgcolor = sc_to_te_color[color & 7] | (color & 8);
	a->ta_bgcolor = sc_to_te_color[(color >> 4) & 7] | ((color >> 4) & 8);
}