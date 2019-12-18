#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int nuses; TYPE_1__* uses; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ ENTRY ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
useeq(ENTRY * e1, ENTRY * e2)
/* are the use references in two entries equivalent? */
{
    unsigned i, j;

    if (e1->nuses != e2->nuses)
	return (FALSE);

    /* Ugh...this is quadratic again */
    for (i = 0; i < e1->nuses; i++) {
	bool foundmatch = FALSE;

	/* search second entry for given use reference */
	for (j = 0; j < e2->nuses; j++)
	    if (!strcmp(e1->uses[i].name, e2->uses[j].name)) {
		foundmatch = TRUE;
		break;
	    }

	if (!foundmatch)
	    return (FALSE);
    }

    return (TRUE);
}