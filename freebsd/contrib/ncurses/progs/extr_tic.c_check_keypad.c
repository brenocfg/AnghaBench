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
typedef  int /*<<< orphan*/  show ;
typedef  int /*<<< orphan*/  TERMTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ANDMISSING (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_KP ; 
 scalar_t__ VALID_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nc_STRCAT (char*,char*,int) ; 
 int /*<<< orphan*/  _nc_warning (char*,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  key_a1 ; 
 int /*<<< orphan*/  key_a3 ; 
 int /*<<< orphan*/  key_b2 ; 
 int /*<<< orphan*/  key_c1 ; 
 int /*<<< orphan*/  key_c3 ; 
 int /*<<< orphan*/  key_dc ; 
 int /*<<< orphan*/  key_ic ; 
 char keypad_final (int /*<<< orphan*/ ) ; 
 long keypad_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
check_keypad(TERMTYPE *tp)
{
    char show[80];

    if (VALID_STRING(key_a1) &&
	VALID_STRING(key_a3) &&
	VALID_STRING(key_b2) &&
	VALID_STRING(key_c1) &&
	VALID_STRING(key_c3)) {
	char final[MAX_KP + 1];
	long list[MAX_KP];
	int increase = 0;
	int j, k, kk;
	long last;
	long test;

	final[0] = keypad_final(key_a1);
	final[1] = keypad_final(key_a3);
	final[2] = keypad_final(key_b2);
	final[3] = keypad_final(key_c1);
	final[4] = keypad_final(key_c3);
	final[5] = '\0';

	/* special case: legacy coding using 1,2,3,0,. on the bottom */
	assert(strlen(final) <= MAX_KP);
	if (!strcmp(final, "qsrpn"))
	    return;

	list[0] = keypad_index(key_a1);
	list[1] = keypad_index(key_a3);
	list[2] = keypad_index(key_b2);
	list[3] = keypad_index(key_c1);
	list[4] = keypad_index(key_c3);

	/* check that they're all vt100 keys */
	for (j = 0; j < MAX_KP; ++j) {
	    if (list[j] < 0) {
		return;
	    }
	}

	/* check if they're all in increasing order */
	for (j = 1; j < MAX_KP; ++j) {
	    if (list[j] > list[j - 1]) {
		++increase;
	    }
	}
	if (increase != (MAX_KP - 1)) {
	    show[0] = '\0';

	    for (j = 0, last = -1; j < MAX_KP; ++j) {
		for (k = 0, kk = -1, test = 100; k < 5; ++k) {
		    if (list[k] > last &&
			list[k] < test) {
			test = list[k];
			kk = k;
		    }
		}
		last = test;
		assert(strlen(show) < (MAX_KP * 4));
		switch (kk) {
		case 0:
		    _nc_STRCAT(show, " ka1", sizeof(show));
		    break;
		case 1:
		    _nc_STRCAT(show, " ka3", sizeof(show));
		    break;
		case 2:
		    _nc_STRCAT(show, " kb2", sizeof(show));
		    break;
		case 3:
		    _nc_STRCAT(show, " kc1", sizeof(show));
		    break;
		case 4:
		    _nc_STRCAT(show, " kc3", sizeof(show));
		    break;
		}
	    }

	    _nc_warning("vt100 keypad order inconsistent: %s", show);
	}

    } else if (VALID_STRING(key_a1) ||
	       VALID_STRING(key_a3) ||
	       VALID_STRING(key_b2) ||
	       VALID_STRING(key_c1) ||
	       VALID_STRING(key_c3)) {
	show[0] = '\0';
	if (keypad_index(key_a1) >= 0)
	    _nc_STRCAT(show, " ka1", sizeof(show));
	if (keypad_index(key_a3) >= 0)
	    _nc_STRCAT(show, " ka3", sizeof(show));
	if (keypad_index(key_b2) >= 0)
	    _nc_STRCAT(show, " kb2", sizeof(show));
	if (keypad_index(key_c1) >= 0)
	    _nc_STRCAT(show, " kc1", sizeof(show));
	if (keypad_index(key_c3) >= 0)
	    _nc_STRCAT(show, " kc3", sizeof(show));
	if (*show != '\0')
	    _nc_warning("vt100 keypad map incomplete:%s", show);
    }

    /*
     * These warnings are useful for consistency checks - it is possible that
     * there are real terminals with mismatches in these
     */
    ANDMISSING(key_ic, key_dc);
}