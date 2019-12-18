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
 int FALSE ; 
 int TRUE ; 
 unsigned int UChar (char) ; 
 scalar_t__ VALID_STRING (char*) ; 
 char* acs_chars ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

void
repair_acsc(TERMTYPE *tp)
{
    if (VALID_STRING(acs_chars)) {
	size_t n, m;
	char mapped[256];
	char extra = 0;
	unsigned source;
	unsigned target;
	bool fix_needed = FALSE;

	for (n = 0, source = 0; acs_chars[n] != 0; n++) {
	    target = UChar(acs_chars[n]);
	    if (source >= target) {
		fix_needed = TRUE;
		break;
	    }
	    source = target;
	    if (acs_chars[n + 1])
		n++;
	}
	if (fix_needed) {
	    memset(mapped, 0, sizeof(mapped));
	    for (n = 0; acs_chars[n] != 0; n++) {
		source = UChar(acs_chars[n]);
		if ((target = (unsigned char) acs_chars[n + 1]) != 0) {
		    mapped[source] = (char) target;
		    n++;
		} else {
		    extra = (char) source;
		}
	    }
	    for (n = m = 0; n < sizeof(mapped); n++) {
		if (mapped[n]) {
		    acs_chars[m++] = (char) n;
		    acs_chars[m++] = mapped[n];
		}
	    }
	    if (extra)
		acs_chars[m++] = extra;		/* garbage in, garbage out */
	    acs_chars[m] = 0;
	}
    }
}