#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct index_state {int cache_nr; struct cache_entry const** cache; } ;
typedef  struct cache_entry {char* name; int ce_flags; } const cache_entry ;

/* Variables and functions */
 int CE_REMOVE ; 
 size_t ce_namelen (struct cache_entry const*) ; 
 int ce_stage (struct cache_entry const*) ; 
 int index_name_stage_pos (struct index_state*,char const*,size_t,int) ; 
 scalar_t__ memcmp (char*,char const*,size_t) ; 
 int /*<<< orphan*/  remove_index_entry_at (struct index_state*,int) ; 
 int strcmp_offset (char const*,char*,size_t*) ; 

__attribute__((used)) static int has_dir_name(struct index_state *istate,
			const struct cache_entry *ce, int pos, int ok_to_replace)
{
	int retval = 0;
	int stage = ce_stage(ce);
	const char *name = ce->name;
	const char *slash = name + ce_namelen(ce);
	size_t len_eq_last;
	int cmp_last = 0;

	/*
	 * We are frequently called during an iteration on a sorted
	 * list of pathnames and while building a new index.  Therefore,
	 * there is a high probability that this entry will eventually
	 * be appended to the index, rather than inserted in the middle.
	 * If we can confirm that, we can avoid binary searches on the
	 * components of the pathname.
	 *
	 * Compare the entry's full path with the last path in the index.
	 */
	if (istate->cache_nr > 0) {
		cmp_last = strcmp_offset(name,
			istate->cache[istate->cache_nr - 1]->name,
			&len_eq_last);
		if (cmp_last > 0) {
			if (len_eq_last == 0) {
				/*
				 * The entry sorts AFTER the last one in the
				 * index and their paths have no common prefix,
				 * so there cannot be a F/D conflict.
				 */
				return retval;
			} else {
				/*
				 * The entry sorts AFTER the last one in the
				 * index, but has a common prefix.  Fall through
				 * to the loop below to disect the entry's path
				 * and see where the difference is.
				 */
			}
		} else if (cmp_last == 0) {
			/*
			 * The entry exactly matches the last one in the
			 * index, but because of multiple stage and CE_REMOVE
			 * items, we fall through and let the regular search
			 * code handle it.
			 */
		}
	}

	for (;;) {
		size_t len;

		for (;;) {
			if (*--slash == '/')
				break;
			if (slash <= ce->name)
				return retval;
		}
		len = slash - name;

		if (cmp_last > 0) {
			/*
			 * (len + 1) is a directory boundary (including
			 * the trailing slash).  And since the loop is
			 * decrementing "slash", the first iteration is
			 * the longest directory prefix; subsequent
			 * iterations consider parent directories.
			 */

			if (len + 1 <= len_eq_last) {
				/*
				 * The directory prefix (including the trailing
				 * slash) also appears as a prefix in the last
				 * entry, so the remainder cannot collide (because
				 * strcmp said the whole path was greater).
				 *
				 * EQ: last: xxx/A
				 *     this: xxx/B
				 *
				 * LT: last: xxx/file_A
				 *     this: xxx/file_B
				 */
				return retval;
			}

			if (len > len_eq_last) {
				/*
				 * This part of the directory prefix (excluding
				 * the trailing slash) is longer than the known
				 * equal portions, so this sub-directory cannot
				 * collide with a file.
				 *
				 * GT: last: xxxA
				 *     this: xxxB/file
				 */
				return retval;
			}

			if (istate->cache_nr > 0 &&
				ce_namelen(istate->cache[istate->cache_nr - 1]) > len) {
				/*
				 * The directory prefix lines up with part of
				 * a longer file or directory name, but sorts
				 * after it, so this sub-directory cannot
				 * collide with a file.
				 *
				 * last: xxx/yy-file (because '-' sorts before '/')
				 * this: xxx/yy/abc
				 */
				return retval;
			}

			/*
			 * This is a possible collision. Fall through and
			 * let the regular search code handle it.
			 *
			 * last: xxx
			 * this: xxx/file
			 */
		}

		pos = index_name_stage_pos(istate, name, len, stage);
		if (pos >= 0) {
			/*
			 * Found one, but not so fast.  This could
			 * be a marker that says "I was here, but
			 * I am being removed".  Such an entry is
			 * not a part of the resulting tree, and
			 * it is Ok to have a directory at the same
			 * path.
			 */
			if (!(istate->cache[pos]->ce_flags & CE_REMOVE)) {
				retval = -1;
				if (!ok_to_replace)
					break;
				remove_index_entry_at(istate, pos);
				continue;
			}
		}
		else
			pos = -pos-1;

		/*
		 * Trivial optimization: if we find an entry that
		 * already matches the sub-directory, then we know
		 * we're ok, and we can exit.
		 */
		while (pos < istate->cache_nr) {
			struct cache_entry *p = istate->cache[pos];
			if ((ce_namelen(p) <= len) ||
			    (p->name[len] != '/') ||
			    memcmp(p->name, name, len))
				break; /* not our subdirectory */
			if (ce_stage(p) == stage && !(p->ce_flags & CE_REMOVE))
				/*
				 * p is at the same stage as our entry, and
				 * is a subdirectory of what we are looking
				 * at, so we cannot have conflicts at our
				 * level or anything shorter.
				 */
				return retval;
			pos++;
		}
	}
	return retval;
}