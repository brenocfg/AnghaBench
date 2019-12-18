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
struct keep {struct keep* next; int /*<<< orphan*/ * sym; } ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 struct keep* keep_list ; 
 scalar_t__ malloc (int) ; 
 char* pname ; 
 int /*<<< orphan*/  stderr ; 
 int strcmp (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strdup (char*) ; 

void
add_to_keep_list(char *symbol)
{
    struct keep *newp, *prevp, *curp;
    int cmp;

    cmp = 0;

    for(curp = keep_list, prevp = NULL; curp; prevp = curp, curp = curp->next)
	if((cmp = strcmp(symbol, curp->sym)) <= 0) break;

    if(curp && cmp == 0)
	return;	/* already in table */

    newp = (struct keep *) malloc(sizeof(struct keep));
    if(newp) newp->sym = strdup(symbol);
    if(newp == NULL || newp->sym == NULL) {
	fprintf(stderr, "%s: out of memory for keep list\n", pname);
	exit(1);
    }

    newp->next = curp;
    if(prevp) prevp->next = newp;
    else keep_list = newp;
}