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
typedef  int /*<<< orphan*/  TERMTYPE ;

/* Variables and functions */
 void* ABSENT_STRING ; 
 int FALSE ; 
 int /*<<< orphan*/  SHOW_WHY (char*) ; 
 int TRUE ; 
 scalar_t__ VALID_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acs_chars ; 
 void* enter_alt_charset_mode ; 
 void* exit_alt_charset_mode ; 
 int /*<<< orphan*/  one_one_mapping (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
purged_acs(TERMTYPE *tterm)
{
    bool result = FALSE;

    if (VALID_STRING(acs_chars)) {
	if (!one_one_mapping(acs_chars)) {
	    enter_alt_charset_mode = ABSENT_STRING;
	    exit_alt_charset_mode = ABSENT_STRING;
	    SHOW_WHY("# (rmacs/smacs removed for consistency)\n");
	}
	result = TRUE;
    }
    return result;
}