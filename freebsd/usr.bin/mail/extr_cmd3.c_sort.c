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
 int /*<<< orphan*/  diction ; 
 int /*<<< orphan*/  qsort (char**,int,int,int /*<<< orphan*/ ) ; 

void
sort(char **list)
{
	char **ap;

	for (ap = list; *ap != NULL; ap++)
		;
	if (ap-list < 2)
		return;
	qsort(list, ap-list, sizeof(*list), diction);
}