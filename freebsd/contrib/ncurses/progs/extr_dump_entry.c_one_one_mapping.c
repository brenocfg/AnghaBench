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
 char const* ABSENT_STRING ; 
 int FALSE ; 
 int TRUE ; 
 scalar_t__ isLine (char const) ; 

__attribute__((used)) static bool
one_one_mapping(const char *mapping)
{
    bool result = TRUE;

    if (mapping != ABSENT_STRING) {
	int n = 0;
	while (mapping[n] != '\0') {
	    if (isLine(mapping[n]) &&
		mapping[n] != mapping[n + 1]) {
		result = FALSE;
		break;
	    }
	    n += 2;
	}
    }
    return result;
}