#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  term_names; } ;
typedef  TYPE_1__ TERMTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ANDMISSING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAIRED (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nc_warning (char*) ; 
 int /*<<< orphan*/  acs_chars ; 
 int /*<<< orphan*/  display_clock ; 
 int /*<<< orphan*/  enter_alt_charset_mode ; 
 int /*<<< orphan*/  enter_am_mode ; 
 int /*<<< orphan*/  enter_blink_mode ; 
 int /*<<< orphan*/  enter_bold_mode ; 
 int /*<<< orphan*/  enter_ca_mode ; 
 int /*<<< orphan*/  enter_delete_mode ; 
 int /*<<< orphan*/  enter_dim_mode ; 
 int /*<<< orphan*/  enter_insert_mode ; 
 int /*<<< orphan*/  enter_italics_mode ; 
 int /*<<< orphan*/  enter_protected_mode ; 
 int /*<<< orphan*/  enter_reverse_mode ; 
 int /*<<< orphan*/  enter_secure_mode ; 
 int /*<<< orphan*/  enter_standout_mode ; 
 int /*<<< orphan*/  enter_underline_mode ; 
 int /*<<< orphan*/  enter_xon_mode ; 
 int /*<<< orphan*/  exit_alt_charset_mode ; 
 int /*<<< orphan*/  exit_am_mode ; 
 int /*<<< orphan*/  exit_attribute_mode ; 
 int /*<<< orphan*/  exit_ca_mode ; 
 int /*<<< orphan*/  exit_delete_mode ; 
 int /*<<< orphan*/  exit_insert_mode ; 
 int /*<<< orphan*/  exit_italics_mode ; 
 int /*<<< orphan*/  exit_standout_mode ; 
 int /*<<< orphan*/  exit_underline_mode ; 
 int /*<<< orphan*/  exit_xon_mode ; 
 int /*<<< orphan*/  fixup_acsc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  from_status_line ; 
 int /*<<< orphan*/  initialize_pair ; 
 int /*<<< orphan*/  label_off ; 
 int /*<<< orphan*/  label_on ; 
 int /*<<< orphan*/  meta_off ; 
 int /*<<< orphan*/  meta_on ; 
 int /*<<< orphan*/  prtr_off ; 
 int /*<<< orphan*/  prtr_on ; 
 int /*<<< orphan*/  remove_clock ; 
 int /*<<< orphan*/  restore_cursor ; 
 int /*<<< orphan*/  save_cursor ; 
 int /*<<< orphan*/  set_attributes ; 
 int /*<<< orphan*/  set_color_pair ; 
 int /*<<< orphan*/  strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  to_status_line ; 

__attribute__((used)) static void
sanity_check2(TERMTYPE *tp, bool literal)
{
    if (!PRESENT(exit_attribute_mode)) {
#ifdef __UNUSED__		/* this casts too wide a net */
	bool terminal_entry = !strchr(tp->term_names, '+');
	if (terminal_entry &&
	    (PRESENT(set_attributes)
	     || PRESENT(enter_standout_mode)
	     || PRESENT(enter_underline_mode)
	     || PRESENT(enter_blink_mode)
	     || PRESENT(enter_bold_mode)
	     || PRESENT(enter_dim_mode)
	     || PRESENT(enter_secure_mode)
	     || PRESENT(enter_protected_mode)
	     || PRESENT(enter_reverse_mode)))
	    _nc_warning("no exit_attribute_mode");
#endif /* __UNUSED__ */
	PAIRED(enter_standout_mode, exit_standout_mode);
	PAIRED(enter_underline_mode, exit_underline_mode);
	PAIRED(enter_italics_mode, exit_italics_mode);
    }

    /* we do this check/fix in postprocess_termcap(), but some packagers
     * prefer to bypass it...
     */
    if (!literal) {
	fixup_acsc(tp, literal);
	ANDMISSING(enter_alt_charset_mode, acs_chars);
	ANDMISSING(exit_alt_charset_mode, acs_chars);
    }

    /* listed in structure-member order of first argument */
    PAIRED(enter_alt_charset_mode, exit_alt_charset_mode);
    ANDMISSING(enter_blink_mode, exit_attribute_mode);
    ANDMISSING(enter_bold_mode, exit_attribute_mode);
    PAIRED(exit_ca_mode, enter_ca_mode);
    PAIRED(enter_delete_mode, exit_delete_mode);
    ANDMISSING(enter_dim_mode, exit_attribute_mode);
    PAIRED(enter_insert_mode, exit_insert_mode);
    ANDMISSING(enter_secure_mode, exit_attribute_mode);
    ANDMISSING(enter_protected_mode, exit_attribute_mode);
    ANDMISSING(enter_reverse_mode, exit_attribute_mode);
    PAIRED(from_status_line, to_status_line);
    PAIRED(meta_off, meta_on);

    PAIRED(prtr_on, prtr_off);
    PAIRED(save_cursor, restore_cursor);
    PAIRED(enter_xon_mode, exit_xon_mode);
    PAIRED(enter_am_mode, exit_am_mode);
    ANDMISSING(label_off, label_on);
#ifdef remove_clock
    PAIRED(display_clock, remove_clock);
#endif
    ANDMISSING(set_color_pair, initialize_pair);
}