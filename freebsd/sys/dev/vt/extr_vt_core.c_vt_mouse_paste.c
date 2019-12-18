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
typedef  char term_char_t ;
struct TYPE_6__ {TYPE_1__* vd_curwindow; } ;
struct TYPE_5__ {int /*<<< orphan*/  vw_terminal; } ;

/* Variables and functions */
 char* VD_PASTEBUF (TYPE_2__*) ; 
 int VD_PASTEBUFLEN (TYPE_2__*) ; 
 TYPE_2__* main_vd ; 
 int /*<<< orphan*/  terminal_input_char (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void
vt_mouse_paste()
{
	term_char_t *buf;
	int i, len;

	len = VD_PASTEBUFLEN(main_vd);
	buf = VD_PASTEBUF(main_vd);
	len /= sizeof(term_char_t);
	for (i = 0; i < len; i++) {
		if (buf[i] == '\0')
			continue;
		terminal_input_char(main_vd->vd_curwindow->vw_terminal,
		    buf[i]);
	}
}