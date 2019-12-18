#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  string_desc ;
typedef  int /*<<< orphan*/  buf2 ;
typedef  int /*<<< orphan*/  TERMTYPE ;

/* Variables and functions */
 int /*<<< orphan*/ * ABSENT_STRING ; 
 int MAX_TERMCAP_LENGTH ; 
 scalar_t__ PRESENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _nc_safe_strcat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nc_save_str (char*) ; 
 int /*<<< orphan*/  _nc_str_init (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  _nc_warning (char*) ; 
 int /*<<< orphan*/  acs_chars ; 
 int /*<<< orphan*/  append_acs0 (int /*<<< orphan*/ *,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * box_chars_1 ; 

__attribute__((used)) static void
postprocess_terminfo(TERMTYPE *tp)
{
    /*
     * TERMINFO-TO-TERMINFO MAPPINGS FOR SOURCE TRANSLATION
     * ----------------------------------------------------------------------
     */

    /*
     * Translate AIX forms characters.
     */
    if (PRESENT(box_chars_1)) {
	char buf2[MAX_TERMCAP_LENGTH];
	string_desc result;

	_nc_str_init(&result, buf2, sizeof(buf2));
	_nc_safe_strcat(&result, acs_chars);

	append_acs0(&result, 'l', box_chars_1[0]);	/* ACS_ULCORNER */
	append_acs0(&result, 'q', box_chars_1[1]);	/* ACS_HLINE */
	append_acs0(&result, 'k', box_chars_1[2]);	/* ACS_URCORNER */
	append_acs0(&result, 'x', box_chars_1[3]);	/* ACS_VLINE */
	append_acs0(&result, 'j', box_chars_1[4]);	/* ACS_LRCORNER */
	append_acs0(&result, 'm', box_chars_1[5]);	/* ACS_LLCORNER */
	append_acs0(&result, 'w', box_chars_1[6]);	/* ACS_TTEE */
	append_acs0(&result, 'u', box_chars_1[7]);	/* ACS_RTEE */
	append_acs0(&result, 'v', box_chars_1[8]);	/* ACS_BTEE */
	append_acs0(&result, 't', box_chars_1[9]);	/* ACS_LTEE */
	append_acs0(&result, 'n', box_chars_1[10]);	/* ACS_PLUS */

	if (buf2[0]) {
	    acs_chars = _nc_save_str(buf2);
	    _nc_warning("acsc string synthesized from AIX capabilities");
	    box_chars_1 = ABSENT_STRING;
	}
    }
    /*
     * ----------------------------------------------------------------------
     */
}