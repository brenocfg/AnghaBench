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
struct algo_needs {int* needs; } ;

/* Variables and functions */
 int ALGO_NEEDS_MAX ; 

int algo_needs_missing(struct algo_needs* n)
{
	int i;
	/* first check if a needed algo was bogus - report that */
	for(i=0; i<ALGO_NEEDS_MAX; i++)
		if(n->needs[i] == 2)
			return 0;
	/* now check which algo is missing */
	for(i=0; i<ALGO_NEEDS_MAX; i++)
		if(n->needs[i] == 1)
			return i;
	return 0;
}