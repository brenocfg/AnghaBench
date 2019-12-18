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
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,size_t) ; 

__attribute__((used)) static bool
has_params(const char *src)
{
    bool result = FALSE;
    int len = (int) strlen(src);
    int n;
    bool ifthen = FALSE;
    bool params = FALSE;

    for (n = 0; n < len - 1; ++n) {
	if (!strncmp(src + n, "%p", (size_t) 2)) {
	    params = TRUE;
	} else if (!strncmp(src + n, "%;", (size_t) 2)) {
	    ifthen = TRUE;
	    result = params;
	    break;
	}
    }
    if (!ifthen) {
	result = ((len > 50) && params);
    }
    return result;
}