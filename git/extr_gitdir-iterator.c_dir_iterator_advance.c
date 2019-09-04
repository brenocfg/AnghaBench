#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct dirent {int /*<<< orphan*/  d_name; } ;
struct dir_iterator_level {int initialized; int prefix_len; scalar_t__ dir_state; int /*<<< orphan*/ * dir; } ;
struct TYPE_7__ {int len; int /*<<< orphan*/ * buf; } ;
struct TYPE_8__ {int /*<<< orphan*/  st_mode; } ;
struct TYPE_6__ {TYPE_2__ path; int /*<<< orphan*/ * basename; int /*<<< orphan*/ * relative_path; TYPE_5__ st; } ;
struct dir_iterator_int {int levels_nr; TYPE_1__ base; struct dir_iterator_level* levels; int /*<<< orphan*/  levels_alloc; } ;
struct dir_iterator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct dir_iterator_level*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ DIR_STATE_ITER ; 
 scalar_t__ DIR_STATE_RECURSE ; 
 scalar_t__ ENOENT ; 
 int ITER_OK ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ closedir (int /*<<< orphan*/ *) ; 
 int dir_iterator_abort (struct dir_iterator*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  is_dir_sep (int /*<<< orphan*/ ) ; 
 scalar_t__ is_dot_or_dotdot (int /*<<< orphan*/ ) ; 
 scalar_t__ lstat (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ *) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addch (TYPE_2__*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_setlen (TYPE_2__*,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int dir_iterator_advance(struct dir_iterator *dir_iterator)
{
	struct dir_iterator_int *iter =
		(struct dir_iterator_int *)dir_iterator;

	while (1) {
		struct dir_iterator_level *level =
			&iter->levels[iter->levels_nr - 1];
		struct dirent *de;

		if (!level->initialized) {
			/*
			 * Note: dir_iterator_begin() ensures that
			 * path is not the empty string.
			 */
			if (!is_dir_sep(iter->base.path.buf[iter->base.path.len - 1]))
				strbuf_addch(&iter->base.path, '/');
			level->prefix_len = iter->base.path.len;

			level->dir = opendir(iter->base.path.buf);
			if (!level->dir && errno != ENOENT) {
				warning("error opening directory %s: %s",
					iter->base.path.buf, strerror(errno));
				/* Popping the level is handled below */
			}

			level->initialized = 1;
		} else if (S_ISDIR(iter->base.st.st_mode)) {
			if (level->dir_state == DIR_STATE_ITER) {
				/*
				 * The directory was just iterated
				 * over; now prepare to iterate into
				 * it.
				 */
				level->dir_state = DIR_STATE_RECURSE;
				ALLOC_GROW(iter->levels, iter->levels_nr + 1,
					   iter->levels_alloc);
				level = &iter->levels[iter->levels_nr++];
				level->initialized = 0;
				continue;
			} else {
				/*
				 * The directory has already been
				 * iterated over and iterated into;
				 * we're done with it.
				 */
			}
		}

		if (!level->dir) {
			/*
			 * This level is exhausted (or wasn't opened
			 * successfully); pop up a level.
			 */
			if (--iter->levels_nr == 0)
				return dir_iterator_abort(dir_iterator);

			continue;
		}

		/*
		 * Loop until we find an entry that we can give back
		 * to the caller:
		 */
		while (1) {
			strbuf_setlen(&iter->base.path, level->prefix_len);
			errno = 0;
			de = readdir(level->dir);

			if (!de) {
				/* This level is exhausted; pop up a level. */
				if (errno) {
					warning("error reading directory %s: %s",
						iter->base.path.buf, strerror(errno));
				} else if (closedir(level->dir))
					warning("error closing directory %s: %s",
						iter->base.path.buf, strerror(errno));

				level->dir = NULL;
				if (--iter->levels_nr == 0)
					return dir_iterator_abort(dir_iterator);
				break;
			}

			if (is_dot_or_dotdot(de->d_name))
				continue;

			strbuf_addstr(&iter->base.path, de->d_name);
			if (lstat(iter->base.path.buf, &iter->base.st) < 0) {
				if (errno != ENOENT)
					warning("error reading path '%s': %s",
						iter->base.path.buf,
						strerror(errno));
				continue;
			}

			/*
			 * We have to set these each time because
			 * the path strbuf might have been realloc()ed.
			 */
			iter->base.relative_path =
				iter->base.path.buf + iter->levels[0].prefix_len;
			iter->base.basename =
				iter->base.path.buf + level->prefix_len;
			level->dir_state = DIR_STATE_ITER;

			return ITER_OK;
		}
	}
}