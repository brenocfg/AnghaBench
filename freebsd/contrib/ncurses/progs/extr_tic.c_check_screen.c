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
struct TYPE_3__ {int /*<<< orphan*/  term_names; } ;
typedef  TYPE_1__ TERMTYPE ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  VALID_BOOLEAN (int) ; 
 scalar_t__ VALID_STRING (int /*<<< orphan*/ ) ; 
 char* _nc_first_name (int /*<<< orphan*/ ) ; 
 scalar_t__ _nc_user_definable ; 
 int /*<<< orphan*/  _nc_warning (char*) ; 
 int back_color_erase ; 
 int /*<<< orphan*/  key_mouse ; 
 scalar_t__ max_colors ; 
 int /*<<< orphan*/  orig_colors ; 
 int /*<<< orphan*/  orig_pair ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strstr (char*,char*) ; 
 int tigetflag (char*) ; 
 int /*<<< orphan*/  to_status_line ; 
 int uses_SGR_39_49 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
check_screen(TERMTYPE *tp)
{
#if NCURSES_XNAMES
    if (_nc_user_definable) {
	int have_XT = tigetflag("XT");
	int have_XM = tigetflag("XM");
	int have_bce = back_color_erase;
	bool have_kmouse = FALSE;
	bool use_sgr_39_49 = FALSE;
	char *name = _nc_first_name(tp->term_names);

	if (!VALID_BOOLEAN(have_bce)) {
	    have_bce = FALSE;
	}
	if (!VALID_BOOLEAN(have_XM)) {
	    have_XM = FALSE;
	}
	if (!VALID_BOOLEAN(have_XT)) {
	    have_XT = FALSE;
	}
	if (VALID_STRING(key_mouse)) {
	    have_kmouse = !strcmp("\033[M", key_mouse);
	}
	if (VALID_STRING(orig_colors)) {
	    use_sgr_39_49 = uses_SGR_39_49(orig_colors);
	} else if (VALID_STRING(orig_pair)) {
	    use_sgr_39_49 = uses_SGR_39_49(orig_pair);
	}

	if (have_XM && have_XT) {
	    _nc_warning("Screen's XT capability conflicts with XM");
	} else if (have_XT
		   && strstr(name, "screen") != 0
		   && strchr(name, '.') != 0) {
	    _nc_warning("Screen's \"screen\" entries should not have XT set");
	} else if (have_XT) {
	    if (!have_kmouse && have_bce) {
		if (VALID_STRING(key_mouse)) {
		    _nc_warning("Value of kmous inconsistent with screen's usage");
		} else {
		    _nc_warning("Expected kmous capability with XT");
		}
	    }
	    if (!have_bce && max_colors > 0)
		_nc_warning("Expected bce capability with XT");
	    if (!use_sgr_39_49 && have_bce && max_colors > 0)
		_nc_warning("Expected orig_colors capability with XT to have 39/49 parameters");
	    if (VALID_STRING(to_status_line))
		_nc_warning("\"tsl\" capability is redundant, given XT");
	} else {
	    if (have_kmouse && !have_XM)
		_nc_warning("Expected XT to be set, given kmous");
	}
    }
#endif
}