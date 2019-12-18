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
typedef  int /*<<< orphan*/  mapped ;
typedef  int /*<<< orphan*/  TERMTYPE ;

/* Variables and functions */
 size_t UChar (char const) ; 
 scalar_t__ VALID_STRING (char*) ; 
 int /*<<< orphan*/  _nc_warning (char*,...) ; 
 char* acs_chars ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
check_acs(TERMTYPE *tp)
{
    if (VALID_STRING(acs_chars)) {
	const char *boxes = "lmkjtuvwqxn";
	char mapped[256];
	char missing[256];
	const char *p;
	char *q;

	memset(mapped, 0, sizeof(mapped));
	for (p = acs_chars; *p != '\0'; p += 2) {
	    if (p[1] == '\0') {
		_nc_warning("acsc has odd number of characters");
		break;
	    }
	    mapped[UChar(p[0])] = p[1];
	}

	if (mapped[UChar('I')] && !mapped[UChar('i')]) {
	    _nc_warning("acsc refers to 'I', which is probably an error");
	}

	for (p = boxes, q = missing; *p != '\0'; ++p) {
	    if (!mapped[UChar(p[0])]) {
		*q++ = p[0];
	    }
	}
	*q = '\0';

	assert(strlen(missing) <= strlen(boxes));
	if (*missing != '\0' && strcmp(missing, boxes)) {
	    _nc_warning("acsc is missing some line-drawing mapping: %s", missing);
	}
    }
}