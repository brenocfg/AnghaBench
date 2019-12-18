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
struct TYPE_3__ {int /*<<< orphan*/  t_defattr; int /*<<< orphan*/  t_curattr; } ;
typedef  TYPE_1__ teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  teken_printf (char*,unsigned int) ; 

__attribute__((used)) static void
teken_subr_cons25_set_graphic_rendition(teken_t *t, unsigned int cmd,
    unsigned int param)
{

	(void)param;
	switch (cmd) {
	case 0: /* Reset. */
		t->t_curattr = t->t_defattr;
		break;
	default:
		teken_printf("unsupported attribute %u\n", cmd);
	}
}