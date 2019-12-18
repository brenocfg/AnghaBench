#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int am_success; int am_failure; } ;
typedef  TYPE_1__ au_mask_t ;
typedef  int /*<<< orphan*/  au_event_t ;
typedef  int au_class_t ;

/* Variables and functions */
 int AU_PRS_FAILURE ; 
 int AU_PRS_SUCCESS ; 

int
au_preselect(au_event_t event, au_class_t class, au_mask_t *mask_p, int sorf)
{
	au_class_t effmask = 0;

	if (mask_p == NULL)
		return (-1);

	/*
	 * Perform the actual check of the masks against the event.
	 */
	if (sorf & AU_PRS_SUCCESS)
		effmask |= (mask_p->am_success & class);

	if (sorf & AU_PRS_FAILURE)
		effmask |= (mask_p->am_failure & class);

	if (effmask)
		return (1);
	else
		return (0);
}