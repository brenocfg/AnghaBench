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
struct terminal {int tm_flags; int /*<<< orphan*/  tm_emulator; int /*<<< orphan*/  tm_mtx; } ;
struct TYPE_5__ {int ta_fgcolor; int ta_bgcolor; } ;
struct TYPE_4__ {int ta_fgcolor; int ta_bgcolor; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_SPIN ; 
 int TC_BLACK ; 
 int TC_LIGHT ; 
 int TC_NCOLORS ; 
 int TC_WHITE ; 
 int TF_CONS ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 TYPE_1__ default_message ; 
 TYPE_2__ kernel_message ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teken_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct terminal*) ; 
 int /*<<< orphan*/  teken_set_defattr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  terminal_drawmethods ; 

__attribute__((used)) static void
terminal_init(struct terminal *tm)
{
	int fg, bg;

	if (tm->tm_flags & TF_CONS)
		mtx_init(&tm->tm_mtx, "trmlck", NULL, MTX_SPIN);

	teken_init(&tm->tm_emulator, &terminal_drawmethods, tm);

	fg = bg = -1;
	TUNABLE_INT_FETCH("teken.fg_color", &fg);
	TUNABLE_INT_FETCH("teken.bg_color", &bg);

	if (fg != -1) {
		default_message.ta_fgcolor = fg;
		kernel_message.ta_fgcolor = fg;
	}
	if (bg != -1) {
		default_message.ta_bgcolor = bg;
		kernel_message.ta_bgcolor = bg;
	}

	if (default_message.ta_bgcolor == TC_WHITE) {
		default_message.ta_bgcolor |= TC_LIGHT;
		kernel_message.ta_bgcolor |= TC_LIGHT;
	}
	
	if (default_message.ta_bgcolor == TC_BLACK &&
	    default_message.ta_fgcolor < TC_NCOLORS)
		kernel_message.ta_fgcolor |= TC_LIGHT;
	teken_set_defattr(&tm->tm_emulator, &default_message);
}