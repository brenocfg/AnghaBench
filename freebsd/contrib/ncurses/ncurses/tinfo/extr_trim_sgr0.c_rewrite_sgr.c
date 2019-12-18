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
 scalar_t__ PRESENT (char*) ; 
 int /*<<< orphan*/  TR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRACE_DATABASE ; 
 int TRUE ; 
 int /*<<< orphan*/  _nc_STRCPY (char*,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,size_t) ; 

__attribute__((used)) static bool
rewrite_sgr(char *s, char *attr)
{
    if (s != 0) {
	if (PRESENT(attr)) {
	    size_t len_s = strlen(s);
	    size_t len_a = strlen(attr);

	    if (len_s > len_a && !strncmp(attr, s, len_a)) {
		unsigned n;
		TR(TRACE_DATABASE, ("rewrite:\n\t%s", s));
		for (n = 0; n < len_s - len_a; ++n) {
		    s[n] = s[n + len_a];
		}
		_nc_STRCPY(s + n, attr, strlen(s) + 1);
		TR(TRACE_DATABASE, ("to:\n\t%s", s));
	    }
	}
	return TRUE;
    }
    return FALSE;		/* oops */
}