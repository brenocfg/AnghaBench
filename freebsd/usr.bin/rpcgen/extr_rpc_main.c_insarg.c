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
 int argcount ; 
 int /*<<< orphan*/ * arglist ; 
 int argmax ; 
 int /*<<< orphan*/  moreargs () ; 
 int /*<<< orphan*/  xstrdup (char const*) ; 

__attribute__((used)) static void
insarg(int place, const char *cp)
{
	int i;

	if (argcount >= argmax)
		moreargs();

	/* Move up existing arguments */
	for (i = argcount - 1; i >= place; i--)
		arglist[i + 1] = arglist[i];

	arglist[place] = xstrdup(cp);
	argcount++;
}