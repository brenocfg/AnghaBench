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

	fprintf(stderr, "%s",
		"usage: pciconf -l [-BbcevV] [device]\n"
		"       pciconf -a device\n"
		"       pciconf -r [-b | -h] device addr[:addr2]\n"
		"       pciconf -w [-b | -h] device addr value\n"
		"       pciconf -D [-b | -h | -x] device bar [start [count]]"
		"\n");
	exit(1);
}