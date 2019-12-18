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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	fprintf(stderr, "%s\n",
"usage: lpr [-Pprinter] [-#num] [-C class] [-J job] [-T title] [-U user]\n"
	"\t[-Z daemon-options] [-i[numcols]] [-i[numcols]] [-1234 font]\n"
	"\t[-L locale] [-wnum] [-cdfghlnmprstv] [name ...]");
	exit(1);
}