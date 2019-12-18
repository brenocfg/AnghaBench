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
struct TYPE_3__ {char* from; char* to; } ;
typedef  TYPE_1__ assoc ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  MAX_TERMINFO_LENGTH ; 
 int TRUE ; 
 int /*<<< orphan*/  _nc_STRCAT (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ same_param (char*,char const*,size_t) ; 
 int strlen (char*) ; 
 char* strtok (char*,char*) ; 

__attribute__((used)) static char *
lookup_params(const assoc * table, char *dst, char *src)
{
    char *result = 0;
    const char *ep = strtok(src, ";");

    if (ep != 0) {
	const assoc *ap;

	do {
	    bool found = FALSE;

	    for (ap = table; ap->from; ap++) {
		size_t tlen = strlen(ap->from);

		if (same_param(ap->from, ep, tlen)) {
		    _nc_STRCAT(dst, ap->to, MAX_TERMINFO_LENGTH);
		    found = TRUE;
		    break;
		}
	    }

	    if (!found)
		_nc_STRCAT(dst, ep, MAX_TERMINFO_LENGTH);
	    _nc_STRCAT(dst, ";", MAX_TERMINFO_LENGTH);
	} while
	    ((ep = strtok((char *) 0, ";")));

	dst[strlen(dst) - 1] = '\0';

	result = dst;
    }
    return result;
}