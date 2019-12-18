#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int ta_fgcolor; } ;
struct TYPE_5__ {unsigned int ta_fgcolor; } ;
struct TYPE_7__ {TYPE_2__ t_curattr; TYPE_1__ t_defattr; } ;
typedef  TYPE_3__ teken_t ;

/* Variables and functions */
 unsigned int* cons25_colors ; 

__attribute__((used)) static void
teken_subr_cons25_set_default_foreground(teken_t *t, unsigned int c)
{

	t->t_defattr.ta_fgcolor = cons25_colors[c % 8] | (c & 8);
	t->t_curattr.ta_fgcolor = cons25_colors[c % 8] | (c & 8);
}