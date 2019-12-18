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
 int /*<<< orphan*/  debugsym (char*,int) ; 
 int findsym (char const**) ; 
 int nsyms ; 
 char** value ; 

__attribute__((used)) static void
indirectsym(void)
{
	const char *cp;
	int changed, sym, ind;

	do {
		changed = 0;
		for (sym = 0; sym < nsyms; ++sym) {
			if (value[sym] == NULL)
				continue;
			cp = value[sym];
			ind = findsym(&cp);
			if (ind == -1 || ind == sym ||
			    *cp != '\0' ||
			    value[ind] == NULL ||
			    value[ind] == value[sym])
				continue;
			debugsym("indir...", sym);
			value[sym] = value[ind];
			debugsym("...ectsym", sym);
			changed++;
		}
	} while (changed);
}