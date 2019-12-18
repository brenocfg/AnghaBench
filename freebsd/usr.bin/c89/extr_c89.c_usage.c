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
usage(void)
{
	fprintf(stderr,
"usage: c89 [-cEgOs] [-D name[=value]] ... [-I directory] ... [-L directory] ...\n"
"           [-o outfile] [-U name] ... operand ...\n"
"\n"
"       where operand is one or more of file.c, file.o, file.a\n"
"       or -llibrary\n");
	exit(1);
}