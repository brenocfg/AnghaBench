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
typedef  scalar_t__ git_submodule_update_t ;
struct TYPE_3__ {int map_value; char const* str_match; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* _sm_update_map ; 

const char *git_submodule_update_to_str(git_submodule_update_t update)
{
	int i;
	for (i = 0; i < (int)ARRAY_SIZE(_sm_update_map); ++i)
		if (_sm_update_map[i].map_value == (int)update)
			return _sm_update_map[i].str_match;
	return NULL;
}