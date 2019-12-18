#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {unsigned int ta_fgcolor; unsigned int ta_bgcolor; } ;
typedef  TYPE_2__ teken_attr_t ;
typedef  int /*<<< orphan*/  env ;
typedef  int UINTN ;
struct TYPE_16__ {char c; TYPE_2__ a; } ;
struct TYPE_15__ {int /*<<< orphan*/  (* SetAttribute ) (TYPE_6__*,int /*<<< orphan*/ ) ;TYPE_1__* Mode; int /*<<< orphan*/  (* QueryMode ) (TYPE_6__*,int /*<<< orphan*/ ,int*,int*) ;} ;
struct TYPE_14__ {int tp_row; int tp_col; } ;
struct TYPE_12__ {int /*<<< orphan*/  Mode; } ;
typedef  int /*<<< orphan*/  EFI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_BGCOLOR ; 
 int /*<<< orphan*/  DEFAULT_FGCOLOR ; 
 scalar_t__ EFI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFI_TEXT_ATTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EV_VOLATILE ; 
 int RB_SERIAL ; 
 int /*<<< orphan*/  bg_c ; 
 TYPE_8__* buffer ; 
 TYPE_6__* conout ; 
 int /*<<< orphan*/  curs_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curx ; 
 int /*<<< orphan*/  cury ; 
 int /*<<< orphan*/  efi_set_colors ; 
 int /*<<< orphan*/  end_term () ; 
 int /*<<< orphan*/  env_nounset ; 
 int /*<<< orphan*/  env_setenv (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fg_c ; 
 int /*<<< orphan*/  free (TYPE_8__*) ; 
 int /*<<< orphan*/  get_pos (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_8__* malloc (int) ; 
 int mode ; 
 int parse_uefi_con_out () ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teken ; 
 TYPE_2__* teken_get_defattr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  teken_set_winsize (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  tf ; 
 TYPE_3__ tp ; 

bool
efi_cons_update_mode(void)
{
	UINTN cols, rows;
	const teken_attr_t *a;
	EFI_STATUS status;
	char env[8];

	status = conout->QueryMode(conout, conout->Mode->Mode, &cols, &rows);
	if (EFI_ERROR(status)) {
		cols = 80;
		rows = 24;
	}

	/*
	 * When we have serial port listed in ConOut, use pre-teken emulator,
	 * if built with.
	 * The problem is, we can not output text on efi and comconsole when
	 * efi also has comconsole bound. But then again, we need to have
	 * terminal emulator for efi text mode to support the menu.
	 * While teken is too expensive to be used on serial console, the
	 * pre-teken emulator is light enough to be used on serial console.
	 */
	mode = parse_uefi_con_out();
	if ((mode & RB_SERIAL) == 0) {
		if (buffer != NULL) {
			if (tp.tp_row == rows && tp.tp_col == cols)
				return (true);
			free(buffer);
		} else {
			teken_init(&teken, &tf, NULL);
		}

		tp.tp_row = rows;
		tp.tp_col = cols;
		buffer = malloc(rows * cols * sizeof(*buffer));
		if (buffer == NULL)
			return (false);

		teken_set_winsize(&teken, &tp);
		a = teken_get_defattr(&teken);

		snprintf(env, sizeof(env), "%d", a->ta_fgcolor);
		env_setenv("teken.fg_color", EV_VOLATILE, env, efi_set_colors,
		    env_nounset);
		snprintf(env, sizeof(env), "%d", a->ta_bgcolor);
		env_setenv("teken.bg_color", EV_VOLATILE, env, efi_set_colors,
		    env_nounset);

		for (int row = 0; row < rows; row++) {
			for (int col = 0; col < cols; col++) {
				buffer[col + row * tp.tp_col].c = ' ';
				buffer[col + row * tp.tp_col].a = *a;
			}
		}
	} else {
#ifdef TERM_EMU
		conout->SetAttribute(conout, EFI_TEXT_ATTR(DEFAULT_FGCOLOR,
		    DEFAULT_BGCOLOR));
		end_term();
		get_pos(&curx, &cury);
		curs_move(&curx, &cury, curx, cury);
		fg_c = DEFAULT_FGCOLOR;
		bg_c = DEFAULT_BGCOLOR;
#endif
	}

	snprintf(env, sizeof (env), "%u", (unsigned)rows);
	setenv("LINES", env, 1);
	snprintf(env, sizeof (env), "%u", (unsigned)cols);
	setenv("COLUMNS", env, 1);

	return (true);
}