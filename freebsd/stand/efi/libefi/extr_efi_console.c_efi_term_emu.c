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
struct TYPE_3__ {int /*<<< orphan*/  (* SetAttribute ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  EFI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  CD () ; 
 int /*<<< orphan*/  CM () ; 
 int DEFAULT_BGCOLOR ; 
 int DEFAULT_FGCOLOR ; 
 int /*<<< orphan*/  EFI_TEXT_ATTR (int,int) ; 
 int /*<<< orphan*/  HO () ; 
 int /*<<< orphan*/  MAXARGS ; 
 size_t argc ; 
 int /*<<< orphan*/ * args ; 
 int /*<<< orphan*/  bail_out (int) ; 
 int bg_c ; 
 TYPE_1__* conout ; 
 int /*<<< orphan*/  efi_cons_rawputchar (int) ; 
 int /*<<< orphan*/  end_term () ; 
 int esc ; 
 int fg_c ; 
 int /*<<< orphan*/  get_arg (int) ; 
 int /*<<< orphan*/  isdigit (int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
efi_term_emu(int c)
{
#ifdef TERM_EMU
	static int ansi_col[] = {
		0, 4, 2, 6, 1, 5, 3, 7
	};
	int t, i;
	EFI_STATUS status;
 
	switch (esc) {
	case 0:
		switch (c) {
		case '\033':
			esc = c;
			break;
		default:
			efi_cons_rawputchar(c);
			break;
		}
		break;
	case '\033':
		switch (c) {
		case '[':
			esc = c;
			args[0] = 0;
			argc = -1;
			break;
		default:
			bail_out(c);
			break;
		}
		break;
	case '[':
		switch (c) {
		case ';':
			if (argc < 0)
				argc = 0;
			else if (argc + 1 >= MAXARGS)
				bail_out(c);
			else
				args[++argc] = 0;
			break;
		case 'H':		/* ho = \E[H */
			if (argc < 0)
				HO();
			else if (argc == 1)
				CM();
			else
				bail_out(c);
			break;
		case 'J':		/* cd = \E[J */
			if (argc < 0)
				CD();
			else
				bail_out(c);
			break;
		case 'm':
			if (argc < 0) {
				fg_c = DEFAULT_FGCOLOR;
				bg_c = DEFAULT_BGCOLOR;
			}
			for (i = 0; i <= argc; ++i) {
				switch (args[i]) {
				case 0:		/* back to normal */
					fg_c = DEFAULT_FGCOLOR;
					bg_c = DEFAULT_BGCOLOR;
					break;
				case 1:		/* bold */
					fg_c |= 0x8;
					break;
				case 4:		/* underline */
				case 5:		/* blink */
					bg_c |= 0x8;
					break;
				case 7:		/* reverse */
					t = fg_c;
					fg_c = bg_c;
					bg_c = t;
					break;
				case 22:	/* normal intensity */
					fg_c &= ~0x8;
					break;
				case 24:	/* not underline */
				case 25:	/* not blinking */
					bg_c &= ~0x8;
					break;
				case 30: case 31: case 32: case 33:
				case 34: case 35: case 36: case 37:
					fg_c = ansi_col[args[i] - 30];
					break;
				case 39:	/* normal */
					fg_c = DEFAULT_FGCOLOR;
					break;
				case 40: case 41: case 42: case 43:
				case 44: case 45: case 46: case 47:
					bg_c = ansi_col[args[i] - 40];
					break;
				case 49:	/* normal */
					bg_c = DEFAULT_BGCOLOR;
					break;
				}
			}
			conout->SetAttribute(conout, EFI_TEXT_ATTR(fg_c, bg_c));
			end_term();
			break;
		default:
			if (isdigit(c))
				get_arg(c);
			else
				bail_out(c);
			break;
		}
		break;
	default:
		bail_out(c);
		break;
	}
#else
	efi_cons_rawputchar(c);
#endif
}