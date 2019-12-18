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
struct stat {int /*<<< orphan*/  st_size; } ;
struct pattern_list {int dummy; } ;
struct oid_stat {int valid; int /*<<< orphan*/  stat; int /*<<< orphan*/  oid; } ;
struct index_state {TYPE_2__** cache; } ;
struct TYPE_5__ {int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {int /*<<< orphan*/ * empty_blob; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  add_patterns_from_buffer (char*,size_t,char const*,int,struct pattern_list*) ; 
 int /*<<< orphan*/  ce_stage (TYPE_2__*) ; 
 scalar_t__ ce_uptodate (TYPE_2__*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fill_stat_data (int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  hash_object_file (char*,size_t,char*,int /*<<< orphan*/ *) ; 
 int index_name_pos (struct index_state*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  match_stat_data_racy (struct index_state*,int /*<<< orphan*/ *,struct stat*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 size_t read_in_full (int,char*,size_t) ; 
 int read_skip_worktree_file_from_index (struct index_state*,char const*,size_t*,char**,struct oid_stat*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 TYPE_1__* the_hash_algo ; 
 int /*<<< orphan*/  warn_on_fopen_errors (char const*) ; 
 int /*<<< orphan*/  would_convert_to_git (struct index_state*,char const*) ; 
 char* xmallocz (size_t) ; 
 size_t xsize_t (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_patterns(const char *fname, const char *base, int baselen,
			struct pattern_list *pl, struct index_state *istate,
			struct oid_stat *oid_stat)
{
	struct stat st;
	int r;
	int fd;
	size_t size = 0;
	char *buf;

	fd = open(fname, O_RDONLY);
	if (fd < 0 || fstat(fd, &st) < 0) {
		if (fd < 0)
			warn_on_fopen_errors(fname);
		else
			close(fd);
		if (!istate)
			return -1;
		r = read_skip_worktree_file_from_index(istate, fname,
						       &size, &buf,
						       oid_stat);
		if (r != 1)
			return r;
	} else {
		size = xsize_t(st.st_size);
		if (size == 0) {
			if (oid_stat) {
				fill_stat_data(&oid_stat->stat, &st);
				oidcpy(&oid_stat->oid, the_hash_algo->empty_blob);
				oid_stat->valid = 1;
			}
			close(fd);
			return 0;
		}
		buf = xmallocz(size);
		if (read_in_full(fd, buf, size) != size) {
			free(buf);
			close(fd);
			return -1;
		}
		buf[size++] = '\n';
		close(fd);
		if (oid_stat) {
			int pos;
			if (oid_stat->valid &&
			    !match_stat_data_racy(istate, &oid_stat->stat, &st))
				; /* no content change, ss->sha1 still good */
			else if (istate &&
				 (pos = index_name_pos(istate, fname, strlen(fname))) >= 0 &&
				 !ce_stage(istate->cache[pos]) &&
				 ce_uptodate(istate->cache[pos]) &&
				 !would_convert_to_git(istate, fname))
				oidcpy(&oid_stat->oid,
				       &istate->cache[pos]->oid);
			else
				hash_object_file(buf, size, "blob",
						 &oid_stat->oid);
			fill_stat_data(&oid_stat->stat, &st);
			oid_stat->valid = 1;
		}
	}

	add_patterns_from_buffer(buf, size, base, baselen, pl);
	return 0;
}