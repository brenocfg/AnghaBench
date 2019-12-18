#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dirent {int /*<<< orphan*/  d_name; } ;
struct dir_iterator_level {int /*<<< orphan*/  dir; int /*<<< orphan*/  prefix_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  buf; } ;
struct TYPE_4__ {int /*<<< orphan*/  st_mode; } ;
struct TYPE_5__ {TYPE_3__ path; TYPE_1__ st; } ;
struct dir_iterator_int {int flags; int levels_nr; TYPE_2__ base; struct dir_iterator_level* levels; } ;
struct dir_iterator {int dummy; } ;

/* Variables and functions */
 int DIR_ITERATOR_PEDANTIC ; 
 scalar_t__ ENOENT ; 
 int ITER_ERROR ; 
 int ITER_OK ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int dir_iterator_abort (struct dir_iterator*) ; 
 scalar_t__ errno ; 
 scalar_t__ is_dot_or_dotdot (int /*<<< orphan*/ ) ; 
 scalar_t__ pop_level (struct dir_iterator_int*) ; 
 scalar_t__ prepare_next_entry_data (struct dir_iterator_int*,struct dirent*) ; 
 scalar_t__ push_level (struct dir_iterator_int*) ; 
 struct dirent* readdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_setlen (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning_errno (char*,int /*<<< orphan*/ ) ; 

int dir_iterator_advance(struct dir_iterator *dir_iterator)
{
	struct dir_iterator_int *iter =
		(struct dir_iterator_int *)dir_iterator;

	if (S_ISDIR(iter->base.st.st_mode) && push_level(iter)) {
		if (errno != ENOENT && iter->flags & DIR_ITERATOR_PEDANTIC)
			goto error_out;
		if (iter->levels_nr == 0)
			goto error_out;
	}

	/* Loop until we find an entry that we can give back to the caller. */
	while (1) {
		struct dirent *de;
		struct dir_iterator_level *level =
			&iter->levels[iter->levels_nr - 1];

		strbuf_setlen(&iter->base.path, level->prefix_len);
		errno = 0;
		de = readdir(level->dir);

		if (!de) {
			if (errno) {
				warning_errno("error reading directory '%s'",
					      iter->base.path.buf);
				if (iter->flags & DIR_ITERATOR_PEDANTIC)
					goto error_out;
			} else if (pop_level(iter) == 0) {
				return dir_iterator_abort(dir_iterator);
			}
			continue;
		}

		if (is_dot_or_dotdot(de->d_name))
			continue;

		if (prepare_next_entry_data(iter, de)) {
			if (errno != ENOENT && iter->flags & DIR_ITERATOR_PEDANTIC)
				goto error_out;
			continue;
		}

		return ITER_OK;
	}

error_out:
	dir_iterator_abort(dir_iterator);
	return ITER_ERROR;
}