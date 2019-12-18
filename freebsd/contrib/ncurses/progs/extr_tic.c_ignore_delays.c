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
 char* skip_delay (char*) ; 

__attribute__((used)) static char *
ignore_delays(char *s)
{
    int delaying = 0;

    do {
	switch (*s) {
	case '$':
	    if (delaying == 0)
		delaying = 1;
	    break;
	case '<':
	    if (delaying == 1)
		delaying = 2;
	    break;
	case '\0':
	    delaying = 0;
	    break;
	default:
	    if (delaying) {
		s = skip_delay(s);
		if (*s == '>')
		    ++s;
		delaying = 0;
	    }
	    break;
	}
	if (delaying)
	    ++s;
    } while (delaying);
    return s;
}