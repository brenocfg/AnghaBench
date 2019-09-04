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
struct oid_stat {int dummy; } ;
struct index_state {TYPE_1__** cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ce_skip_worktree (TYPE_1__*) ; 
 int do_read_blob (int /*<<< orphan*/ *,struct oid_stat*,size_t*,char**) ; 
 int index_name_pos (struct index_state const*,char const*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int read_skip_worktree_file_from_index(const struct index_state *istate,
					      const char *path,
					      size_t *size_out, char **data_out,
					      struct oid_stat *oid_stat)
{
	int pos, len;

	len = strlen(path);
	pos = index_name_pos(istate, path, len);
	if (pos < 0)
		return -1;
	if (!ce_skip_worktree(istate->cache[pos]))
		return -1;

	return do_read_blob(&istate->cache[pos]->oid, oid_stat, size_out, data_out);
}