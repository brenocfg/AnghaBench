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
 scalar_t__ _nc_name_match (char const*,char*,char*) ; 

__attribute__((used)) static bool
matches(char **needle, const char *haystack)
/* does entry in needle list match |-separated field in haystack? */
{
    bool code = FALSE;
    size_t n;

    if (needle != 0) {
	for (n = 0; needle[n] != 0; n++) {
	    if (_nc_name_match(haystack, needle[n], "|")) {
		code = TRUE;
		break;
	    }
	}
    } else
	code = TRUE;
    return (code);
}