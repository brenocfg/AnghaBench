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
	fprintf(stderr, "usage: athregs [-i interface] [-abdkmqxz]\n");
	fprintf(stderr, "-a	display all registers\n");
	fprintf(stderr, "-b	display baseband registers\n");
	fprintf(stderr, "-d	display DCU registers\n");
	fprintf(stderr, "-k	display key cache registers\n");
	fprintf(stderr, "-m	display \"MAC\" registers (default)\n");
	fprintf(stderr, "-q	display QCU registers\n");
	fprintf(stderr, "-x	display XR registers\n");
	fprintf(stderr, "-z	display interrupt registers\n");
	fprintf(stderr, "\n");
	fprintf(stderr, "-A	display register address\n");
	fprintf(stderr, "-N	suppress display of register name\n");
	exit(-1);
}