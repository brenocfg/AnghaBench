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

__attribute__((used)) static bool
is_termcap(const char *string)
{
    bool result = TRUE;

    if (string == 0 || *string == '\0') {
	result = FALSE;		/* tparm() handles empty strings */
    } else {
	while ((*string != '\0') && result) {
	    if (*string == '%') {
		switch (*++string) {
		case 'p':
		    result = FALSE;
		    break;
		case '\0':
		    string--;
		    break;
		}
	    } else if (string[0] == '$' && string[1] == '<') {
		result = FALSE;
	    }
	    string++;
	}
    }
    return result;
}