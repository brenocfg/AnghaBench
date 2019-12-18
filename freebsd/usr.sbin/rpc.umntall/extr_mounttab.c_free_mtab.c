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
struct mtablist {struct mtablist* mtab_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct mtablist*) ; 
 struct mtablist* mtabhead ; 

void
free_mtab(void)
{
	struct mtablist *mtabp;

	while ((mtabp = mtabhead) != NULL) {
		mtabhead = mtabhead->mtab_next;
		free(mtabp);
	}
}