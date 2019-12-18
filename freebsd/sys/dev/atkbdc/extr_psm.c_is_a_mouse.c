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
 int FALSE ; 
#define  PSM_BALLPOINT_ID 131 
#define  PSM_EXPLORER_ID 130 
#define  PSM_INTELLI_ID 129 
#define  PSM_MOUSE_ID 128 
 int TRUE ; 

__attribute__((used)) static int
is_a_mouse(int id)
{
#if 0
	static int valid_ids[] = {
		PSM_MOUSE_ID,		/* mouse */
		PSM_BALLPOINT_ID,	/* ballpoint device */
		PSM_INTELLI_ID,		/* Intellimouse */
		PSM_EXPLORER_ID,	/* Intellimouse Explorer */
		-1			/* end of table */
	};
	int i;

	for (i = 0; valid_ids[i] >= 0; ++i)
	if (valid_ids[i] == id)
		return (TRUE);
	return (FALSE);
#else
	return (TRUE);
#endif
}