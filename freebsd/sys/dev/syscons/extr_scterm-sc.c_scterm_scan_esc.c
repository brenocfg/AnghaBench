#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_30__ {int bg; int fg; } ;
struct TYPE_29__ {int fg; int bg; } ;
struct TYPE_31__ {int esc; int saved_xpos; int saved_ypos; int last_param; int num_param; int* param; int attr_mask; void* cur_attr; TYPE_2__ rev_color; TYPE_1__ std_color; TYPE_1__ cur_color; TYPE_2__ dflt_rev_color; TYPE_1__ dflt_std_color; } ;
typedef  TYPE_3__ term_stat ;
typedef  int /*<<< orphan*/  tcattrs ;
struct TYPE_32__ {int xpos; int ypos; int xsize; int border; int bell_pitch; int bell_duration; int /*<<< orphan*/  font_size; int /*<<< orphan*/  cursor_pos; int /*<<< orphan*/  vtb; TYPE_5__* sc; } ;
typedef  TYPE_4__ scr_stat ;
struct TYPE_33__ {TYPE_4__* cur_scp; int /*<<< orphan*/ * scr_map; } ;
typedef  TYPE_5__ sc_softc_t ;
typedef  int /*<<< orphan*/  cattrs ;

/* Variables and functions */
 int BG_CHANGED ; 
 int BLINK_ATTR ; 
 int BOLD_ATTR ; 
#define  CONS_BLINK_CURSOR 148 
#define  CONS_CHAR_CURSOR 147 
#define  CONS_HIDDEN_CURSOR 146 
#define  CONS_LOCAL_CURSOR 145 
#define  CONS_RESET_CURSOR 144 
#define  FG_BLACK 143 
#define  FG_BLUE 142 
#define  FG_BROWN 141 
 int FG_CHANGED ; 
#define  FG_CYAN 140 
#define  FG_DARKGREY 139 
#define  FG_GREEN 138 
#define  FG_LIGHTBLUE 137 
#define  FG_LIGHTCYAN 136 
#define  FG_LIGHTGREEN 135 
#define  FG_LIGHTGREY 134 
#define  FG_LIGHTMAGENTA 133 
#define  FG_LIGHTRED 132 
#define  FG_MAGENTA 131 
#define  FG_RED 130 
#define  FG_WHITE 129 
#define  FG_YELLOW 128 
 int MAX_ESC_PAR ; 
 void* NORMAL_ATTR ; 
 int REVERSE_ATTR ; 
 int UNDERLINE_ATTR ; 
 int hz ; 
 int /*<<< orphan*/  mark_for_update (TYPE_4__*,int /*<<< orphan*/ ) ; 
 void* mask2attr (TYPE_3__*) ; 
 int /*<<< orphan*/  sc_change_cursor_shape (TYPE_4__*,int const,int,int) ; 
 int /*<<< orphan*/  sc_clear_screen (TYPE_4__*) ; 
 int /*<<< orphan*/  sc_move_cursor (TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  sc_set_border (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sc_switch_scr (TYPE_5__*,int) ; 
 int /*<<< orphan*/  sc_term_backtab (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sc_term_clr_eol (TYPE_4__*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sc_term_clr_eos (TYPE_4__*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sc_term_col (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sc_term_del_char (TYPE_4__*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sc_term_del_line (TYPE_4__*,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_term_down (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_term_ins_char (TYPE_4__*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sc_term_ins_line (TYPE_4__*,int,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_term_left (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sc_term_right (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sc_term_row (TYPE_4__*,int) ; 
 int /*<<< orphan*/  sc_term_up (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_term_up_scroll (TYPE_4__*,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_vtb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void
scterm_scan_esc(scr_stat *scp, term_stat *tcp, u_char c)
{
	static u_char ansi_col[16] = {
		FG_BLACK,     FG_RED,          FG_GREEN,      FG_BROWN,
		FG_BLUE,      FG_MAGENTA,      FG_CYAN,       FG_LIGHTGREY,
		FG_DARKGREY,  FG_LIGHTRED,     FG_LIGHTGREEN, FG_YELLOW,
		FG_LIGHTBLUE, FG_LIGHTMAGENTA, FG_LIGHTCYAN,  FG_WHITE
	};
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
		CONS_BLINK_CURSOR | CONS_LOCAL_CURSOR,	/* very visible */
	};
	sc_softc_t *sc;
	int v0, v1, v2;
	int i, n;

	i = n = 0;
	sc = scp->sc; 
	if (tcp->esc == 1) {	/* seen ESC */
		switch (c) {

		case '7':	/* Save cursor position */
			tcp->saved_xpos = scp->xpos;
			tcp->saved_ypos = scp->ypos;
			break;

		case '8':	/* Restore saved cursor position */
			if (tcp->saved_xpos >= 0 && tcp->saved_ypos >= 0)
				sc_move_cursor(scp, tcp->saved_xpos,
					       tcp->saved_ypos);
			break;

		case '[':	/* Start ESC [ sequence */
			tcp->esc = 2;
			tcp->last_param = -1;
			for (i = tcp->num_param; i < MAX_ESC_PAR; i++)
				tcp->param[i] = 1;
			tcp->num_param = 0;
			return;

		case 'M':	/* Move cursor up 1 line, scroll if at top */
			sc_term_up_scroll(scp, 1, sc->scr_map[0x20],
					  tcp->cur_attr, 0, 0);
			break;
#ifdef notyet
		case 'Q':
			tcp->esc = 4;
			return;
#endif
		case 'c':       /* reset */
			tcp->attr_mask = NORMAL_ATTR;
			tcp->cur_color = tcp->std_color
				       = tcp->dflt_std_color;
			tcp->rev_color = tcp->dflt_rev_color;
			tcp->cur_attr = mask2attr(tcp);
			sc_change_cursor_shape(scp,
			    CONS_RESET_CURSOR | CONS_LOCAL_CURSOR, -1, -1);
			sc_clear_screen(scp);
			break;

		case '(':	/* iso-2022: designate 94 character set to G0 */
			tcp->esc = 5;
			return;
		}
	} else if (tcp->esc == 2) {	/* seen ESC [ */
		if (c >= '0' && c <= '9') {
			if (tcp->num_param < MAX_ESC_PAR) {
				if (tcp->last_param != tcp->num_param) {
					tcp->last_param = tcp->num_param;
					tcp->param[tcp->num_param] = 0;
				} else {
					tcp->param[tcp->num_param] *= 10;
				}
				tcp->param[tcp->num_param] += c - '0';
				return;
			}
		}
		tcp->num_param = tcp->last_param + 1;
		switch (c) {

		case ';':
			if (tcp->num_param < MAX_ESC_PAR)
				return;
			break;

		case '=':
			tcp->esc = 3;
			tcp->last_param = -1;
			for (i = tcp->num_param; i < MAX_ESC_PAR; i++)
				tcp->param[i] = 1;
			tcp->num_param = 0;
			return;

		case 'A':	/* up n rows */
			sc_term_up(scp, tcp->param[0], 0);
			break;

		case 'B':	/* down n rows */
			sc_term_down(scp, tcp->param[0], 0);
			break;

		case 'C':	/* right n columns */
			sc_term_right(scp, tcp->param[0]);
			break;

		case 'D':	/* left n columns */
			sc_term_left(scp, tcp->param[0]);
			break;

		case 'E':	/* cursor to start of line n lines down */
			n = tcp->param[0];
			if (n < 1)
				n = 1;
			sc_move_cursor(scp, 0, scp->ypos + n);
			break;

		case 'F':	/* cursor to start of line n lines up */
			n = tcp->param[0];
			if (n < 1)
				n = 1;
			sc_move_cursor(scp, 0, scp->ypos - n);
			break;

		case 'f':	/* Cursor move */
		case 'H':
			if (tcp->num_param == 0)
				sc_move_cursor(scp, 0, 0);
			else if (tcp->num_param == 2)
				sc_move_cursor(scp, tcp->param[1] - 1,
					       tcp->param[0] - 1);
			break;

		case 'J':	/* Clear all or part of display */
			if (tcp->num_param == 0)
				n = 0;
			else
				n = tcp->param[0];
			sc_term_clr_eos(scp, n, sc->scr_map[0x20],
					tcp->cur_attr);
			break;

		case 'K':	/* Clear all or part of line */
			if (tcp->num_param == 0)
				n = 0;
			else
				n = tcp->param[0];
			sc_term_clr_eol(scp, n, sc->scr_map[0x20],
					tcp->cur_attr);
			break;

		case 'L':	/* Insert n lines */
			sc_term_ins_line(scp, scp->ypos, tcp->param[0],
					 sc->scr_map[0x20], tcp->cur_attr, 0);
			break;

		case 'M':	/* Delete n lines */
			sc_term_del_line(scp, scp->ypos, tcp->param[0],
					 sc->scr_map[0x20], tcp->cur_attr, 0);
			break;

		case 'P':	/* Delete n chars */
			sc_term_del_char(scp, tcp->param[0],
					 sc->scr_map[0x20], tcp->cur_attr);
			break;

		case '@':	/* Insert n chars */
			sc_term_ins_char(scp, tcp->param[0],
					 sc->scr_map[0x20], tcp->cur_attr);
			break;

		case 'S':	/* scroll up n lines */
			sc_term_del_line(scp, 0, tcp->param[0],
					 sc->scr_map[0x20], tcp->cur_attr, 0);
			break;

		case 'T':	/* scroll down n lines */
			sc_term_ins_line(scp, 0, tcp->param[0],
					 sc->scr_map[0x20], tcp->cur_attr, 0);
			break;

		case 'X':	/* erase n characters in line */
			n = tcp->param[0];
			if (n < 1)
				n = 1;
			if (n > scp->xsize - scp->xpos)
				n = scp->xsize - scp->xpos;
			sc_vtb_erase(&scp->vtb, scp->cursor_pos, n,
				     sc->scr_map[0x20], tcp->cur_attr);
			mark_for_update(scp, scp->cursor_pos);
			mark_for_update(scp, scp->cursor_pos + n - 1);
			break;

		case 'Z':	/* move n tabs backwards */
			sc_term_backtab(scp, tcp->param[0]);
			break;

		case '`':	/* move cursor to column n */
			sc_term_col(scp, tcp->param[0]);
			break;

		case 'a':	/* move cursor n columns to the right */
			sc_term_right(scp, tcp->param[0]);
			break;

		case 'd':	/* move cursor to row n */
			sc_term_row(scp, tcp->param[0]);
			break;

		case 'e':	/* move cursor n rows down */
			sc_term_down(scp, tcp->param[0], 0);
			break;

		case 'm':	/* change attribute */
			if (tcp->num_param == 0) {
				tcp->attr_mask = NORMAL_ATTR;
				tcp->cur_color = tcp->std_color;
				tcp->cur_attr = mask2attr(tcp);
				break;
			}
			for (i = 0; i < tcp->num_param; i++) {
				switch (n = tcp->param[i]) {
				case 0:	/* back to normal */
					tcp->attr_mask = NORMAL_ATTR;
					tcp->cur_color = tcp->std_color;
					tcp->cur_attr = mask2attr(tcp);
					break;
				case 1:	/* bold */
					tcp->attr_mask |= BOLD_ATTR;
					tcp->cur_attr = mask2attr(tcp);
					break;
				case 4:	/* underline */
					tcp->attr_mask |= UNDERLINE_ATTR;
					tcp->cur_attr = mask2attr(tcp);
					break;
				case 5:	/* blink */
					tcp->attr_mask |= BLINK_ATTR;
					tcp->cur_attr = mask2attr(tcp);
					break;
				case 7: /* reverse */
					tcp->attr_mask |= REVERSE_ATTR;
					tcp->cur_attr = mask2attr(tcp);
					break;
				case 22: /* remove bold (or dim) */
					tcp->attr_mask &= ~BOLD_ATTR;
					tcp->cur_attr = mask2attr(tcp);
					break;
				case 24: /* remove underline */
					tcp->attr_mask &= ~UNDERLINE_ATTR;
					tcp->cur_attr = mask2attr(tcp);
					break;
				case 25: /* remove blink */
					tcp->attr_mask &= ~BLINK_ATTR;
					tcp->cur_attr = mask2attr(tcp);
					break;
				case 27: /* remove reverse */
					tcp->attr_mask &= ~REVERSE_ATTR;
					tcp->cur_attr = mask2attr(tcp);
					break;
				case 30: case 31: /* set ansi fg color */
				case 32: case 33: case 34:
				case 35: case 36: case 37:
					tcp->attr_mask |= FG_CHANGED;
					tcp->cur_color.fg = ansi_col[n - 30];
					tcp->cur_attr = mask2attr(tcp);
					break;
				case 39: /* restore fg color back to normal */
					tcp->attr_mask &= ~(FG_CHANGED|BOLD_ATTR);
					tcp->cur_color.fg = tcp->std_color.fg;
					tcp->cur_attr = mask2attr(tcp);
					break;
				case 40: case 41: /* set ansi bg color */
				case 42: case 43: case 44:
				case 45: case 46: case 47:
					tcp->attr_mask |= BG_CHANGED;
					tcp->cur_color.bg = ansi_col[n - 40];
					tcp->cur_attr = mask2attr(tcp);
		    			break;
				case 49: /* restore bg color back to normal */
					tcp->attr_mask &= ~BG_CHANGED;
					tcp->cur_color.bg = tcp->std_color.bg;
					tcp->cur_attr = mask2attr(tcp);
					break;
				}
			}
			break;

		case 's':	/* Save cursor position */
			tcp->saved_xpos = scp->xpos;
			tcp->saved_ypos = scp->ypos;
			break;

		case 'u':	/* Restore saved cursor position */
			if (tcp->saved_xpos >= 0 && tcp->saved_ypos >= 0)
				sc_move_cursor(scp, tcp->saved_xpos,
					       tcp->saved_ypos);
			break;

		case 'x':
			if (tcp->num_param == 0)
				n = 0;
			else
				n = tcp->param[0];
			switch (n) {
			case 0: /* reset colors and attributes back to normal */
				tcp->attr_mask = NORMAL_ATTR;
				tcp->cur_color = tcp->std_color
					       = tcp->dflt_std_color;
				tcp->rev_color = tcp->dflt_rev_color;
				tcp->cur_attr = mask2attr(tcp);
				break;
			case 1:	/* set ansi background */
				tcp->attr_mask &= ~BG_CHANGED;
				tcp->cur_color.bg = tcp->std_color.bg
						  = ansi_col[tcp->param[1] & 0x0f];
				tcp->cur_attr = mask2attr(tcp);
				break;
			case 2:	/* set ansi foreground */
				tcp->attr_mask &= ~FG_CHANGED;
				tcp->cur_color.fg = tcp->std_color.fg
						  = ansi_col[tcp->param[1] & 0x0f];
				tcp->cur_attr = mask2attr(tcp);
				break;
			case 3: /* set adapter attribute directly */
				tcp->attr_mask &= ~(FG_CHANGED | BG_CHANGED);
				tcp->cur_color.fg = tcp->std_color.fg
						  = tcp->param[1] & 0x0f;
				tcp->cur_color.bg = tcp->std_color.bg
						  = (tcp->param[1] >> 4) & 0x0f;
				tcp->cur_attr = mask2attr(tcp);
				break;
			case 5: /* set ansi reverse background */
				tcp->rev_color.bg = ansi_col[tcp->param[1] & 0x0f];
				tcp->cur_attr = mask2attr(tcp);
				break;
			case 6: /* set ansi reverse foreground */
				tcp->rev_color.fg = ansi_col[tcp->param[1] & 0x0f];
				tcp->cur_attr = mask2attr(tcp);
				break;
			case 7: /* set adapter reverse attribute directly */
				tcp->rev_color.fg = tcp->param[1] & 0x0f;
				tcp->rev_color.bg = (tcp->param[1] >> 4) & 0x0f;
				tcp->cur_attr = mask2attr(tcp);
				break;
			}
			break;

		case 'z':	/* switch to (virtual) console n */
			if (tcp->num_param == 1)
				sc_switch_scr(sc, tcp->param[0]);
			break;
		}
	} else if (tcp->esc == 3) {	/* seen ESC [0-9]+ = */
		if (c >= '0' && c <= '9') {
			if (tcp->num_param < MAX_ESC_PAR) {
				if (tcp->last_param != tcp->num_param) {
					tcp->last_param = tcp->num_param;
					tcp->param[tcp->num_param] = 0;
				} else {
					tcp->param[tcp->num_param] *= 10;
				}
				tcp->param[tcp->num_param] += c - '0';
				return;
			}
		}
		tcp->num_param = tcp->last_param + 1;
		switch (c) {

		case ';':
			if (tcp->num_param < MAX_ESC_PAR)
				return;
			break;

		case 'A':   /* set display border color */
			if (tcp->num_param == 1) {
				scp->border=tcp->param[0] & 0xff;
				if (scp == sc->cur_scp)
					sc_set_border(scp, scp->border);
			}
			break;

		case 'B':   /* set bell pitch and duration */
			if (tcp->num_param == 2) {
				scp->bell_pitch = tcp->param[0];
				scp->bell_duration = 
				    (tcp->param[1] * hz + 99) / 100;
			}
			break;

		case 'C':   /* set global/parmanent cursor type & shape */
			i = spltty();
			n = tcp->num_param;
			v0 = tcp->param[0];
			v1 = tcp->param[1];
			v2 = tcp->param[2];
			switch (n) {
			case 1:	/* flags only */
				if (v0 < sizeof(cattrs)/sizeof(cattrs[0]))
					v0 = cattrs[v0];
				else	/* backward compatibility */
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
			splx(i);
			break;

		case 'F':   /* set adapter foreground */
			if (tcp->num_param == 1) {
				tcp->attr_mask &= ~FG_CHANGED;
				tcp->cur_color.fg = tcp->std_color.fg
						  = tcp->param[0] & 0x0f;
				tcp->cur_attr = mask2attr(tcp);
			}
			break;

		case 'G':   /* set adapter background */
			if (tcp->num_param == 1) {
				tcp->attr_mask &= ~BG_CHANGED;
				tcp->cur_color.bg = tcp->std_color.bg
						  = tcp->param[0] & 0x0f;
				tcp->cur_attr = mask2attr(tcp);
			}
			break;

		case 'H':   /* set adapter reverse foreground */
			if (tcp->num_param == 1) {
				tcp->rev_color.fg = tcp->param[0] & 0x0f;
				tcp->cur_attr = mask2attr(tcp);
			}
			break;

		case 'I':   /* set adapter reverse background */
			if (tcp->num_param == 1) {
				tcp->rev_color.bg = tcp->param[0] & 0x0f;
				tcp->cur_attr = mask2attr(tcp);
			}
			break;

		case 'S':   /* set local/temporary cursor type & shape */
			i = spltty();
			n = tcp->num_param;
			v0 = tcp->param[0];
			switch (n) {
			case 0:
				v0 = 0;
				/* FALL THROUGH */
			case 1:
				if (v0 < sizeof(tcattrs)/sizeof(tcattrs[0]))
					sc_change_cursor_shape(scp,
					    tcattrs[v0], -1, -1);
				break;
			}
			splx(i);
			break;
		}
#ifdef notyet
	} else if (tcp->esc == 4) {	/* seen ESC Q */
		/* to be filled */
#endif
	} else if (tcp->esc == 5) {	/* seen ESC ( */
		switch (c) {
		case 'B':   /* iso-2022: desginate ASCII into G0 */
			break;
		/* other items to be filled */
		default:
			break;
		}
	}
	tcp->esc = 0;
}