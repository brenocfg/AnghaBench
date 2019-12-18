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
struct TYPE_3__ {int sl_cur; int sl_max; char** sl_str; } ;
typedef  TYPE_1__ StringList ;

/* Variables and functions */
 scalar_t__ _SL_CHUNKSIZE ; 
 char** reallocf (char**,int) ; 

int
sl_add(StringList *sl, char *name)
{
	if (sl->sl_cur == sl->sl_max - 1) {
		sl->sl_max += _SL_CHUNKSIZE;
		sl->sl_str = reallocf(sl->sl_str, sl->sl_max * sizeof(char *));
		if (sl->sl_str == NULL)
			return (-1);
	}
	sl->sl_str[sl->sl_cur++] = name;
	return (0);
}