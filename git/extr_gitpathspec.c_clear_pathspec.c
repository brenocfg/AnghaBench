#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pathspec {int nr; TYPE_2__* items; } ;
struct TYPE_4__ {int attr_match_nr; scalar_t__ attr_check; TYPE_1__* attr_match; TYPE_1__* original; TYPE_1__* match; } ;
struct TYPE_3__ {struct TYPE_3__* value; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (TYPE_2__*) ; 
 int /*<<< orphan*/  attr_check_free (scalar_t__) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void clear_pathspec(struct pathspec *pathspec)
{
	int i, j;

	for (i = 0; i < pathspec->nr; i++) {
		free(pathspec->items[i].match);
		free(pathspec->items[i].original);

		for (j = 0; j < pathspec->items[i].attr_match_nr; j++)
			free(pathspec->items[i].attr_match[j].value);
		free(pathspec->items[i].attr_match);

		if (pathspec->items[i].attr_check)
			attr_check_free(pathspec->items[i].attr_check);
	}

	FREE_AND_NULL(pathspec->items);
	pathspec->nr = 0;
}