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
typedef  scalar_t__ wchar_t ;

/* Variables and functions */
 scalar_t__* realloc (scalar_t__*,int) ; 
 int wideidx ; 
 scalar_t__* widestr ; 
 int widesz ; 
 int /*<<< orphan*/  yyerror (char*) ; 

void
add_wcs(wchar_t c)
{
	if ((wideidx + 1) >= widesz) {
		widesz += 64;
		widestr = realloc(widestr, (widesz * sizeof (wchar_t)));
		if (widestr == NULL) {
			yyerror("out of memory");
			wideidx = 0;
			widesz = 0;
			return;
		}
	}

	widestr[wideidx++] = c;
	widestr[wideidx] = 0;
}