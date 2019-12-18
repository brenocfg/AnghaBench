#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {TYPE_2__ path; } ;
struct dir_iterator_level {int levels_nr; TYPE_1__ base; struct dir_iterator_level* levels; int /*<<< orphan*/  prefix_len; scalar_t__ dir; } ;
struct dir_iterator_int {int levels_nr; TYPE_1__ base; struct dir_iterator_int* levels; int /*<<< orphan*/  prefix_len; scalar_t__ dir; } ;
struct dir_iterator {int dummy; } ;

/* Variables and functions */
 int ITER_DONE ; 
 scalar_t__ closedir (scalar_t__) ; 
 int errno ; 
 int /*<<< orphan*/  free (struct dir_iterator_level*) ; 
 int /*<<< orphan*/  strbuf_release (TYPE_2__*) ; 
 int /*<<< orphan*/  strbuf_setlen (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning_errno (char*,int /*<<< orphan*/ ) ; 

int dir_iterator_abort(struct dir_iterator *dir_iterator)
{
	struct dir_iterator_int *iter = (struct dir_iterator_int *)dir_iterator;

	for (; iter->levels_nr; iter->levels_nr--) {
		struct dir_iterator_level *level =
			&iter->levels[iter->levels_nr - 1];

		if (level->dir && closedir(level->dir)) {
			int saved_errno = errno;
			strbuf_setlen(&iter->base.path, level->prefix_len);
			errno = saved_errno;
			warning_errno("error closing directory '%s'",
				      iter->base.path.buf);
		}
	}

	free(iter->levels);
	strbuf_release(&iter->base.path);
	free(iter);
	return ITER_DONE;
}