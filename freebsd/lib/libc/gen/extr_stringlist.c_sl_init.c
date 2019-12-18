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
struct TYPE_3__ {int sl_max; int /*<<< orphan*/ * sl_str; scalar_t__ sl_cur; } ;
typedef  TYPE_1__ StringList ;

/* Variables and functions */
 int _SL_CHUNKSIZE ; 
 int /*<<< orphan*/  _err (int,char*) ; 
 void* malloc (int) ; 

StringList *
sl_init(void)
{
	StringList *sl;

	sl = malloc(sizeof(StringList));
	if (sl == NULL)
		_err(1, "stringlist: %m");

	sl->sl_cur = 0;
	sl->sl_max = _SL_CHUNKSIZE;
	sl->sl_str = malloc(sl->sl_max * sizeof(char *));
	if (sl->sl_str == NULL)
		_err(1, "stringlist: %m");
	return sl;
}