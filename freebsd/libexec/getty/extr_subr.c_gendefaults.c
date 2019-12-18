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
struct gettystrs {scalar_t__ value; int /*<<< orphan*/  defalt; scalar_t__ field; } ;
struct gettynums {int /*<<< orphan*/  value; int /*<<< orphan*/  defalt; scalar_t__ set; scalar_t__ field; } ;
struct gettyflags {int /*<<< orphan*/  invrt; int /*<<< orphan*/  defalt; int /*<<< orphan*/  value; scalar_t__ set; scalar_t__ field; } ;

/* Variables and functions */
 struct gettyflags* gettyflags ; 
 struct gettynums* gettynums ; 
 struct gettystrs* gettystrs ; 
 int /*<<< orphan*/  strdup (scalar_t__) ; 

void
gendefaults(void)
{
	struct gettystrs *sp;
	struct gettynums *np;
	struct gettyflags *fp;

	for (sp = gettystrs; sp->field; sp++)
		if (sp->value)
			sp->defalt = strdup(sp->value);
	for (np = gettynums; np->field; np++)
		if (np->set)
			np->defalt = np->value;
	for (fp = gettyflags; fp->field; fp++)
		if (fp->set)
			fp->defalt = fp->value;
		else
			fp->defalt = fp->invrt;
}