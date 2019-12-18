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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(int exit_code)
{
    fprintf(stderr, "Usage: telnetd");
    fprintf(stderr, " [--help]");
    fprintf(stderr, " [--version]");
#ifdef	AUTHENTICATION
    fprintf(stderr, " [-a (debug|other|otp|user|valid|off|none)]\n\t");
#endif
    fprintf(stderr, " [-debug]");
#ifdef DIAGNOSTICS
    fprintf(stderr, " [-D (options|report|exercise|netdata|ptydata)]\n\t");
#endif
#ifdef	AUTHENTICATION
    fprintf(stderr, " [-edebug]");
#endif
    fprintf(stderr, " [-h]");
    fprintf(stderr, " [-L login]");
    fprintf(stderr, " [-n]");
#ifdef	_CRAY
    fprintf(stderr, " [-r[lowpty]-[highpty]]");
#endif
    fprintf(stderr, "\n\t");
#ifdef	HAVE_GETTOSBYNAME
    fprintf(stderr, " [-S tos]");
#endif
#ifdef	AUTHENTICATION
    fprintf(stderr, " [-X auth-type] [-y] [-z]");
#endif
    fprintf(stderr, " [-u utmp_hostname_length] [-U]");
    fprintf(stderr, " [port]\n");
    exit(exit_code);
}