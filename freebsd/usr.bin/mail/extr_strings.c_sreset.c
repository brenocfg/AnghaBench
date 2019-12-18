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
struct strings {int s_nleft; int /*<<< orphan*/ * s_topFree; int /*<<< orphan*/ * s_nextFree; } ;

/* Variables and functions */
 size_t NSPACE ; 
 int STRINGSIZE ; 
 scalar_t__ noreset ; 
 struct strings* stringdope ; 

void
sreset(void)
{
	struct strings *sp;
	int index;

	if (noreset)
		return;
	index = 0;
	for (sp = &stringdope[0]; sp < &stringdope[NSPACE]; sp++) {
		if (sp->s_topFree == NULL)
			continue;
		sp->s_nextFree = sp->s_topFree;
		sp->s_nleft = STRINGSIZE << index;
		index++;
	}
}