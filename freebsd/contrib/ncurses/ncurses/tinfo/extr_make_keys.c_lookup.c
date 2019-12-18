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
 int UNKNOWN ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 
 scalar_t__* strfnames ; 
 scalar_t__* strnames ; 

__attribute__((used)) static unsigned
lookup(const char *name)
{
    unsigned n;
    bool found = FALSE;
    for (n = 0; strnames[n] != 0; n++) {
	if (!strcmp(name, strnames[n])) {
	    found = TRUE;
	    break;
	}
    }
    if (!found) {
	for (n = 0; strfnames[n] != 0; n++) {
	    if (!strcmp(name, strfnames[n])) {
		found = TRUE;
		break;
	    }
	}
    }
    return found ? n : UNKNOWN;
}