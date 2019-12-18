#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* cchar; char* fmt; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ PR ;

/* Variables and functions */
 int /*<<< orphan*/  F_BPAD ; 
 scalar_t__ strchr (char const*,char) ; 

void
bpad(PR *pr)
{
	static char const *spec = " -0+#";
	char *p1, *p2;

	/*
	 * Remove all conversion flags; '-' is the only one valid
	 * with %s, and it's not useful here.
	 */
	pr->flags = F_BPAD;
	pr->cchar[0] = 's';
	pr->cchar[1] = '\0';
	for (p1 = pr->fmt; *p1 != '%'; ++p1);
	for (p2 = ++p1; *p1 && strchr(spec, *p1); ++p1);
	while ((*p2++ = *p1++));
}