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
 int /*<<< orphan*/  WR (char const*,int) ; 
 int strlen (char const*) ; 

void
printfn(const char *fn, int print_nl)
{

	if (print_nl)
		WR("\n", 1);
	WR("==> ", 4);
	WR(fn, strlen(fn));
	WR(" <==\n", 5);
}