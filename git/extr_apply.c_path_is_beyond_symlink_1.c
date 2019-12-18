#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct strbuf {size_t len; char* buf; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct cache_entry {int /*<<< orphan*/  ce_mode; } ;
struct apply_state {TYPE_1__* repo; scalar_t__ check_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 unsigned int APPLY_SYMLINK_GOES_AWAY ; 
 unsigned int APPLY_SYMLINK_IN_RESULT ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 unsigned int check_symlink_changes (struct apply_state*,char*) ; 
 int /*<<< orphan*/  ignore_case ; 
 struct cache_entry* index_file_exists (int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstat (char*,struct stat*) ; 

__attribute__((used)) static int path_is_beyond_symlink_1(struct apply_state *state, struct strbuf *name)
{
	do {
		unsigned int change;

		while (--name->len && name->buf[name->len] != '/')
			; /* scan backwards */
		if (!name->len)
			break;
		name->buf[name->len] = '\0';
		change = check_symlink_changes(state, name->buf);
		if (change & APPLY_SYMLINK_IN_RESULT)
			return 1;
		if (change & APPLY_SYMLINK_GOES_AWAY)
			/*
			 * This cannot be "return 0", because we may
			 * see a new one created at a higher level.
			 */
			continue;

		/* otherwise, check the preimage */
		if (state->check_index) {
			struct cache_entry *ce;

			ce = index_file_exists(state->repo->index, name->buf,
					       name->len, ignore_case);
			if (ce && S_ISLNK(ce->ce_mode))
				return 1;
		} else {
			struct stat st;
			if (!lstat(name->buf, &st) && S_ISLNK(st.st_mode))
				return 1;
		}
	} while (1);
	return 0;
}