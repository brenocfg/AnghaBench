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
struct mpt_drive_list {int ndrives; struct mpt_drive_list** drives; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct mpt_drive_list*) ; 

void
mpt_free_pd_list(struct mpt_drive_list *list)
{
	int i;

	for (i = 0; i < list->ndrives; i++)
		free(list->drives[i]);
	free(list);
}