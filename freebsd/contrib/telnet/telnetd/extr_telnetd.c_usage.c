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

void
usage()
{
	fprintf(stderr, "usage: telnetd");
#ifdef	AUTHENTICATION
	fprintf(stderr,
	    " [-4] [-6] [-a (debug|other|user|valid|off|none)]\n\t");
#endif
#ifdef BFTPDAEMON
	fprintf(stderr, " [-B]");
#endif
	fprintf(stderr, " [-debug]");
#ifdef DIAGNOSTICS
	fprintf(stderr, " [-D (options|report|exercise|netdata|ptydata)]\n\t");
#endif
#ifdef	AUTHENTICATION
	fprintf(stderr, " [-edebug]");
#endif
	fprintf(stderr, " [-h]");
#if	defined(LINEMODE) && defined(KLUDGELINEMODE)
	fprintf(stderr, " [-k]");
#endif
#ifdef LINEMODE
	fprintf(stderr, " [-l]");
#endif
	fprintf(stderr, " [-n]");
	fprintf(stderr, "\n\t");
#ifdef	HAS_GETTOS
	fprintf(stderr, " [-S tos]");
#endif
#ifdef	AUTHENTICATION
	fprintf(stderr, " [-X auth-type]");
#endif
	fprintf(stderr, " [-u utmp_hostname_length] [-U]");
	fprintf(stderr, " [port]\n");
	exit(1);
}