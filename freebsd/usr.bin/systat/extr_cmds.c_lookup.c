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
struct cmdtab {char* c_name; } ;

/* Variables and functions */
 struct cmdtab* cmdtab ; 

struct cmdtab *
lookup(const char *name)
{
	const char *p, *q;
	struct cmdtab *ct, *found;
	int nmatches, longest;

	longest = 0;
	nmatches = 0;
	found = (struct cmdtab *) 0;
	for (ct = cmdtab; (p = ct->c_name); ct++) {
		for (q = name; *q == *p++; q++)
			if (*q == 0)		/* exact match? */
				return (ct);
		if (!*q) {			/* the name was a prefix */
			if (q - name > longest) {
				longest = q - name;
				nmatches = 1;
				found = ct;
			} else if (q - name == longest)
				nmatches++;
		}
	}
	if (nmatches > 1)
		return ((struct cmdtab *)-1);
	return (found);
}