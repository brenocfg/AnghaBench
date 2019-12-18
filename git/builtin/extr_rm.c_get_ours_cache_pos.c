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
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 TYPE_1__** active_cache ; 
 int active_nr ; 
 int ce_stage (TYPE_1__*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int get_ours_cache_pos(const char *path, int pos)
{
	int i = -pos - 1;

	while ((i < active_nr) && !strcmp(active_cache[i]->name, path)) {
		if (ce_stage(active_cache[i]) == 2)
			return i;
		i++;
	}
	return -1;
}