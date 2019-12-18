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
struct dir_iterator_level {int /*<<< orphan*/ * dir; } ;
struct TYPE_3__ {int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {TYPE_1__ path; } ;
struct dir_iterator_int {int levels_nr; TYPE_2__ base; struct dir_iterator_level* levels; } ;

/* Variables and functions */
 scalar_t__ closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warning_errno (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pop_level(struct dir_iterator_int *iter)
{
	struct dir_iterator_level *level =
		&iter->levels[iter->levels_nr - 1];

	if (level->dir && closedir(level->dir))
		warning_errno("error closing directory '%s'",
			      iter->base.path.buf);
	level->dir = NULL;

	return --iter->levels_nr;
}