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
struct TYPE_4__ {int ta_format; int /*<<< orphan*/  ta_bgcolor; int /*<<< orphan*/  ta_fgcolor; } ;
struct TYPE_5__ {TYPE_1__ t_defattr; } ;
typedef  TYPE_2__ teken_t ;

/* Variables and functions */
 int TF_BOLD ; 
 int* cons25_revcolors ; 
 size_t teken_256to8 (int /*<<< orphan*/ ) ; 

void
teken_get_defattr_cons25(const teken_t *t, int *fg, int *bg)
{

	*fg = cons25_revcolors[teken_256to8(t->t_defattr.ta_fgcolor)];
	if (t->t_defattr.ta_format & TF_BOLD)
		*fg += 8;
	*bg = cons25_revcolors[teken_256to8(t->t_defattr.ta_bgcolor)];
}