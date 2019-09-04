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
struct index_state {int cache_nr; TYPE_1__** cache; } ;
struct dir_struct {int nr; struct dir_entry** entries; } ;
struct dir_entry {char* name; int len; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int,char*) ; 
 int ce_namelen (TYPE_1__*) ; 
 scalar_t__ ce_stage (TYPE_1__*) ; 
 int index_name_pos (struct index_state const*,char*,int) ; 
 int /*<<< orphan*/  show_dir_entry (struct index_state const*,int /*<<< orphan*/ ,struct dir_entry*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  tag_killed ; 

__attribute__((used)) static void show_killed_files(const struct index_state *istate,
			      const struct dir_struct *dir)
{
	int i;
	for (i = 0; i < dir->nr; i++) {
		struct dir_entry *ent = dir->entries[i];
		char *cp, *sp;
		int pos, len, killed = 0;

		for (cp = ent->name; cp - ent->name < ent->len; cp = sp + 1) {
			sp = strchr(cp, '/');
			if (!sp) {
				/* If ent->name is prefix of an entry in the
				 * cache, it will be killed.
				 */
				pos = index_name_pos(istate, ent->name, ent->len);
				if (0 <= pos)
					BUG("killed-file %.*s not found",
						ent->len, ent->name);
				pos = -pos - 1;
				while (pos < istate->cache_nr &&
				       ce_stage(istate->cache[pos]))
					pos++; /* skip unmerged */
				if (istate->cache_nr <= pos)
					break;
				/* pos points at a name immediately after
				 * ent->name in the cache.  Does it expect
				 * ent->name to be a directory?
				 */
				len = ce_namelen(istate->cache[pos]);
				if ((ent->len < len) &&
				    !strncmp(istate->cache[pos]->name,
					     ent->name, ent->len) &&
				    istate->cache[pos]->name[ent->len] == '/')
					killed = 1;
				break;
			}
			if (0 <= index_name_pos(istate, ent->name, sp - ent->name)) {
				/* If any of the leading directories in
				 * ent->name is registered in the cache,
				 * ent->name will be killed.
				 */
				killed = 1;
				break;
			}
		}
		if (killed)
			show_dir_entry(istate, tag_killed, dir->entries[i]);
	}
}