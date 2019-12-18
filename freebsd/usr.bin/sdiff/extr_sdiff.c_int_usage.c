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
 int /*<<< orphan*/  puts (char*) ; 

__attribute__((used)) static void
int_usage(void)
{

	puts("e:\tedit blank diff\n"
	    "eb:\tedit both diffs concatenated\n"
	    "el:\tedit left diff\n"
	    "er:\tedit right diff\n"
	    "l | 1:\tchoose left diff\n"
	    "r | 2:\tchoose right diff\n"
	    "s:\tsilent mode--don't print identical lines\n"
	    "v:\tverbose mode--print identical lines\n"
	    "q:\tquit");
}