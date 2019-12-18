#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int nuses; TYPE_1__* uses; } ;
struct TYPE_4__ {char* name; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_2__ ENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
print_uses(ENTRY * ep, FILE *fp)
/* print an entry's use references */
{
    unsigned i;

    if (!ep->nuses)
	fputs("NULL", fp);
    else
	for (i = 0; i < ep->nuses; i++) {
	    fputs(ep->uses[i].name, fp);
	    if (i < ep->nuses - 1)
		fputs(" ", fp);
	}
}