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
 int /*<<< orphan*/  STDERR_FILENO ; 
 char* character (int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  write (int /*<<< orphan*/ ,char*,int) ; 

void
echo_stderr(int n)
{
    static int need_lf;
    char *s;

    switch (n) {
    case '\r':		/* ignore '\r' */
	break;
    case -1:
	if (need_lf == 0)
	    break;
	/* FALLTHROUGH */
    case '\n':
	write(STDERR_FILENO, "\n", 1);
	need_lf = 0;
	break;
    default:
	s = character(n);
	write(STDERR_FILENO, s, strlen(s));
	need_lf = 1;
	break;
    }
}