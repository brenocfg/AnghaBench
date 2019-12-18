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
 int /*<<< orphan*/  NCURSES_PATHSEP ; 
 int /*<<< orphan*/  _nc_STRCPY (char*,char const*,size_t) ; 
 char* my_blob ; 
 int strlen (char*) ; 

__attribute__((used)) static void
add_to_blob(const char *text, size_t limit)
{
    (void) limit;

    if (*text != '\0') {
	char *last = my_blob + strlen(my_blob);
	if (last != my_blob)
	    *last++ = NCURSES_PATHSEP;
	_nc_STRCPY(last, text, limit);
    }
}