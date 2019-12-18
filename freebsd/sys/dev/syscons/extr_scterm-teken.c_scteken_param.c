#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tcattrs ;
struct TYPE_6__ {int const flags; } ;
struct TYPE_7__ {unsigned int border; unsigned int mouse_level; int /*<<< orphan*/  bell_duration; int /*<<< orphan*/  bell_pitch; TYPE_3__* sc; TYPE_1__ base_curs_attr; int /*<<< orphan*/  font_size; } ;
typedef  TYPE_2__ scr_stat ;
typedef  int /*<<< orphan*/  cattrs ;
struct TYPE_8__ {TYPE_2__* cur_scp; } ;

/* Variables and functions */
#define  CONS_BLINK_CURSOR 139 
#define  CONS_CHAR_CURSOR 138 
#define  CONS_HIDDEN_CURSOR 137 
#define  CONS_LOCAL_CURSOR 136 
#define  CONS_RESET_CURSOR 135 
#define  TP_MOUSE 134 
#define  TP_SETBELLPD 133 
 int /*<<< orphan*/  TP_SETBELLPD_DURATION (unsigned int) ; 
 int /*<<< orphan*/  TP_SETBELLPD_PITCH (unsigned int) ; 
#define  TP_SETBORDER 132 
#define  TP_SETGLOBALCURSOR 131 
#define  TP_SETLOCALCURSOR 130 
#define  TP_SHOWCURSOR 129 
#define  TP_SWITCHVT 128 
 int /*<<< orphan*/  sc_change_cursor_shape (TYPE_2__*,int const,int,int) ; 
 int /*<<< orphan*/  sc_set_border (TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  sc_switch_scr (TYPE_3__*,unsigned int) ; 

__attribute__((used)) static void
scteken_param(void *arg, int cmd, unsigned int value)
{
	static int cattrs[] = {
		0,					/* block */
		CONS_BLINK_CURSOR,			/* blinking block */
		CONS_CHAR_CURSOR,			/* underline */
		CONS_CHAR_CURSOR | CONS_BLINK_CURSOR,	/* blinking underline */
		CONS_RESET_CURSOR,			/* reset to default */
		CONS_HIDDEN_CURSOR,			/* hide cursor */
	};
	static int tcattrs[] = {
		CONS_RESET_CURSOR | CONS_LOCAL_CURSOR,	/* normal */
		CONS_HIDDEN_CURSOR | CONS_LOCAL_CURSOR,	/* invisible */
	};
	scr_stat *scp = arg;
	int flags, n, v0, v1, v2;

	switch (cmd) {
	case TP_SETBORDER:
		scp->border = value & 0xff;
		if (scp == scp->sc->cur_scp)
			sc_set_border(scp, scp->border);
		break;
	case TP_SETGLOBALCURSOR:
		n = value & 0xff;
		v0 = (value >> 8) & 0xff;
		v1 = (value >> 16) & 0xff;
		v2 = (value >> 24) & 0xff;
		switch (n) {
		case 1:	/* flags only */
			if (v0 < sizeof(cattrs) / sizeof(cattrs[0]))
				v0 = cattrs[v0];
			else /* backward compatibility */
				v0 = cattrs[v0 & 0x3];
			sc_change_cursor_shape(scp, v0, -1, -1);
			break;
		case 2:
			v2 = 0;
			v0 &= 0x1f;	/* backward compatibility */
			v1 &= 0x1f;
			/* FALL THROUGH */
		case 3:	/* base and height */
			if (v2 == 0)	/* count from top */
				sc_change_cursor_shape(scp, -1,
				    scp->font_size - v1 - 1,
				    v1 - v0 + 1);
			else if (v2 == 1) /* count from bottom */
				sc_change_cursor_shape(scp, -1,
				    v0, v1 - v0 + 1);
			break;
		}
		break;
	case TP_SETLOCALCURSOR:
		if (value < sizeof(tcattrs) / sizeof(tcattrs[0]))
			sc_change_cursor_shape(scp, tcattrs[value], -1, -1);
		else if (value == 2) {
			sc_change_cursor_shape(scp,
			    CONS_RESET_CURSOR | CONS_LOCAL_CURSOR, -1, -1);
			flags = scp->base_curs_attr.flags ^ CONS_BLINK_CURSOR;
			sc_change_cursor_shape(scp,
			    flags | CONS_LOCAL_CURSOR, -1, -1);
		}
		break;
	case TP_SHOWCURSOR:
		if (value != 0)
			flags = scp->base_curs_attr.flags & ~CONS_HIDDEN_CURSOR;
		else
			flags = scp->base_curs_attr.flags | CONS_HIDDEN_CURSOR;
		sc_change_cursor_shape(scp, flags | CONS_LOCAL_CURSOR, -1, -1);
		break;
	case TP_SWITCHVT:
		sc_switch_scr(scp->sc, value);
		break;
	case TP_SETBELLPD:
		scp->bell_pitch = TP_SETBELLPD_PITCH(value);
		scp->bell_duration = TP_SETBELLPD_DURATION(value);
		break;
	case TP_MOUSE:
		scp->mouse_level = value;
		break;
	}
}