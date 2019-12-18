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
struct TYPE_4__ {unsigned int ta_fgcolor; unsigned int ta_bgcolor; int /*<<< orphan*/  ta_format; } ;
struct TYPE_5__ {TYPE_1__ t_curattr; TYPE_1__ t_defattr; } ;
typedef  TYPE_2__ teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  TF_BLINK ; 
 int /*<<< orphan*/  TF_BOLD ; 
 int /*<<< orphan*/  TF_REVERSE ; 
 int /*<<< orphan*/  TF_UNDERLINE ; 
 int /*<<< orphan*/  teken_printf (char*,unsigned int) ; 

__attribute__((used)) static void
teken_subr_set_graphic_rendition(teken_t *t, unsigned int ncmds,
    const unsigned int cmds[])
{
	unsigned int i, n;

	/* No attributes means reset. */
	if (ncmds == 0) {
		t->t_curattr = t->t_defattr;
		return;
	}

	for (i = 0; i < ncmds; i++) {
		n = cmds[i];

		switch (n) {
		case 0: /* Reset. */
			t->t_curattr = t->t_defattr;
			break;
		case 1: /* Bold. */
			t->t_curattr.ta_format |= TF_BOLD;
			break;
		case 4: /* Underline. */
			t->t_curattr.ta_format |= TF_UNDERLINE;
			break;
		case 5: /* Blink. */
			t->t_curattr.ta_format |= TF_BLINK;
			break;
		case 7: /* Reverse. */
			t->t_curattr.ta_format |= TF_REVERSE;
			break;
		case 22: /* Remove bold. */
			t->t_curattr.ta_format &= ~TF_BOLD;
			break;
		case 24: /* Remove underline. */
			t->t_curattr.ta_format &= ~TF_UNDERLINE;
			break;
		case 25: /* Remove blink. */
			t->t_curattr.ta_format &= ~TF_BLINK;
			break;
		case 27: /* Remove reverse. */
			t->t_curattr.ta_format &= ~TF_REVERSE;
			break;
		case 30: /* Set foreground color: black */
		case 31: /* Set foreground color: red */
		case 32: /* Set foreground color: green */
		case 33: /* Set foreground color: brown */
		case 34: /* Set foreground color: blue */
		case 35: /* Set foreground color: magenta */
		case 36: /* Set foreground color: cyan */
		case 37: /* Set foreground color: white */
			t->t_curattr.ta_fgcolor = n - 30;
			break;
		case 38: /* Set foreground color: 256 color mode */
			if (i + 2 >= ncmds || cmds[i + 1] != 5)
				continue;
			t->t_curattr.ta_fgcolor = cmds[i + 2];
			i += 2;
			break;
		case 39: /* Set default foreground color. */
			t->t_curattr.ta_fgcolor = t->t_defattr.ta_fgcolor;
			break;
		case 40: /* Set background color: black */
		case 41: /* Set background color: red */
		case 42: /* Set background color: green */
		case 43: /* Set background color: brown */
		case 44: /* Set background color: blue */
		case 45: /* Set background color: magenta */
		case 46: /* Set background color: cyan */
		case 47: /* Set background color: white */
			t->t_curattr.ta_bgcolor = n - 40;
			break;
		case 48: /* Set background color: 256 color mode */
			if (i + 2 >= ncmds || cmds[i + 1] != 5)
				continue;
			t->t_curattr.ta_bgcolor = cmds[i + 2];
			i += 2;
			break;
		case 49: /* Set default background color. */
			t->t_curattr.ta_bgcolor = t->t_defattr.ta_bgcolor;
			break;
		case 90: /* Set bright foreground color: black */
		case 91: /* Set bright foreground color: red */
		case 92: /* Set bright foreground color: green */
		case 93: /* Set bright foreground color: brown */
		case 94: /* Set bright foreground color: blue */
		case 95: /* Set bright foreground color: magenta */
		case 96: /* Set bright foreground color: cyan */
		case 97: /* Set bright foreground color: white */
			t->t_curattr.ta_fgcolor = (n - 90) + 8;
			break;
		case 100: /* Set bright background color: black */
		case 101: /* Set bright background color: red */
		case 102: /* Set bright background color: green */
		case 103: /* Set bright background color: brown */
		case 104: /* Set bright background color: blue */
		case 105: /* Set bright background color: magenta */
		case 106: /* Set bright background color: cyan */
		case 107: /* Set bright background color: white */
			t->t_curattr.ta_bgcolor = (n - 100) + 8;
			break;
		default:
			teken_printf("unsupported attribute %u\n", n);
		}
	}
}