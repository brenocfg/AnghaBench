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
struct keep {int /*<<< orphan*/  sym; struct keep* next; } ;

/* Variables and functions */
 struct keep* keep_list ; 
 int strcmp (char const*,int /*<<< orphan*/ ) ; 

int
in_keep_list(const char *symbol)
{
    struct keep *curp;
    int cmp;

    cmp = 0;

    for(curp = keep_list; curp; curp = curp->next)
	if((cmp = strcmp(symbol, curp->sym)) <= 0) break;

    return curp && cmp == 0;
}