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
 int LAST_VISIBLE_CONTENTS ; 

int VisibleContents (int contents)
{
	int		i;

	for (i=1 ; i<=LAST_VISIBLE_CONTENTS ; i<<=1)
		if (contents & i )
			return i;

	return 0;
}