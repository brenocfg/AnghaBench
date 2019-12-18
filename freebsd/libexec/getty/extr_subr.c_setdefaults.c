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
struct gettystrs {scalar_t__ defalt; scalar_t__ value; scalar_t__ field; } ;
struct gettynums {int /*<<< orphan*/  defalt; int /*<<< orphan*/  value; int /*<<< orphan*/  set; scalar_t__ field; } ;
struct gettyflags {int /*<<< orphan*/  defalt; int /*<<< orphan*/  value; int /*<<< orphan*/  set; scalar_t__ field; } ;

/* Variables and functions */
 struct gettyflags* gettyflags ; 
 struct gettynums* gettynums ; 
 struct gettystrs* gettystrs ; 
 scalar_t__ strdup (scalar_t__) ; 

void
setdefaults(void)
{
	struct gettystrs *sp;
	struct gettynums *np;
	struct gettyflags *fp;

	for (sp = gettystrs; sp->field; sp++)
		if (!sp->value)
			sp->value = !sp->defalt ? sp->defalt
						: strdup(sp->defalt);
	for (np = gettynums; np->field; np++)
		if (!np->set)
			np->value = np->defalt;
	for (fp = gettyflags; fp->field; fp++)
		if (!fp->set)
			fp->value = fp->defalt;
}