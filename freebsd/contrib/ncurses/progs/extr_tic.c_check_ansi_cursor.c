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

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 char UChar (char) ; 
 char* _nc_tic_expand (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nc_warning (char*,char*,...) ; 
 scalar_t__ isdigit (char) ; 
 scalar_t__ memcmp (char*,char*,size_t) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static void
check_ansi_cursor(char *list[4])
{
    int j, k;
    int want;
    size_t prefix = 0;
    size_t suffix;
    bool skip[4];
    bool repeated = FALSE;

    for (j = 0; j < 4; ++j) {
	skip[j] = FALSE;
	for (k = 0; k < j; ++k) {
	    if (j != k
		&& !strcmp(list[j], list[k])) {
		char *value = _nc_tic_expand(list[k], TRUE, 0);
		_nc_warning("repeated cursor control %s\n", value);
		repeated = TRUE;
	    }
	}
    }
    if (!repeated) {
	char *up = list[1];

	if (UChar(up[0]) == '\033') {
	    if (up[1] == '[') {
		prefix = 2;
	    } else {
		prefix = 1;
	    }
	} else if (UChar(up[0]) == UChar('\233')) {
	    prefix = 1;
	}
	if (prefix) {
	    suffix = prefix;
	    while (up[suffix] && isdigit(UChar(up[suffix])))
		++suffix;
	}
	if (prefix && up[suffix] == 'A') {
	    skip[1] = TRUE;
	    if (!strcmp(list[0], "\n"))
		skip[0] = TRUE;
	    if (!strcmp(list[2], "\b"))
		skip[2] = TRUE;

	    for (j = 0; j < 4; ++j) {
		if (skip[j] || strlen(list[j]) == 1)
		    continue;
		if (memcmp(list[j], up, prefix)) {
		    char *value = _nc_tic_expand(list[j], TRUE, 0);
		    _nc_warning("inconsistent prefix for %s\n", value);
		    continue;
		}
		if (strlen(list[j]) < suffix) {
		    char *value = _nc_tic_expand(list[j], TRUE, 0);
		    _nc_warning("inconsistent length for %s, expected %d\n",
				value, (int) suffix + 1);
		    continue;
		}
		want = "BADC"[j];
		if (list[j][suffix] != want) {
		    char *value = _nc_tic_expand(list[j], TRUE, 0);
		    _nc_warning("inconsistent suffix for %s, expected %c, have %c\n",
				value, want, list[j][suffix]);
		}
	    }
	}
    }
}