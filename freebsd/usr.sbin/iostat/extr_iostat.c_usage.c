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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
usage(void)
{
	/*
	 * We also support the following 'traditional' syntax:
	 * iostat [drives] [wait [count]]
	 * This isn't mentioned in the man page, or the usage statement,
	 * but it is supported.
	 */
	fprintf(stderr, "usage: iostat [-CdhIKoTxz?] [-c count] [-M core]"
		" [-n devs] [-N system]\n"
		"\t      [-t type,if,pass] [-w wait] [drives]\n");
}