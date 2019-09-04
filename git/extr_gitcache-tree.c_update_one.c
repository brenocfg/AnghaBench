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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
typedef  struct object_id {int /*<<< orphan*/  hash; } const object_id ;
struct cache_tree_sub {int count; int used; struct cache_tree* cache_tree; } ;
struct cache_tree {int entry_count; int subtree_nr; struct object_id const oid; TYPE_1__** down; } ;
struct cache_entry {char* name; unsigned int ce_mode; int ce_flags; struct object_id const oid; } ;
struct TYPE_4__ {int /*<<< orphan*/  rawsz; } ;
struct TYPE_3__ {scalar_t__ used; } ;

/* Variables and functions */
 int CE_REMOVE ; 
 unsigned int S_IFDIR ; 
 unsigned int S_IFGITLINK ; 
 int WRITE_TREE_DRY_RUN ; 
 int WRITE_TREE_MISSING_OK ; 
 int WRITE_TREE_REPAIR ; 
 int /*<<< orphan*/  assert (int) ; 
 struct cache_tree* cache_tree () ; 
 scalar_t__ ce_intent_to_add (struct cache_entry const*) ; 
 int ce_namelen (struct cache_entry const*) ; 
 scalar_t__ ce_skip_worktree (struct cache_entry const*) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 int /*<<< orphan*/  discard_unused_subtrees (struct cache_tree*) ; 
 int error (char*,unsigned int,char*,int,char const*) ; 
 struct cache_tree_sub* find_subtree (struct cache_tree*,char const*,int,int) ; 
 scalar_t__ has_object_file (struct object_id const*) ; 
 int /*<<< orphan*/  hash_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id const*) ; 
 scalar_t__ is_empty_tree_oid (struct object_id const*) ; 
 scalar_t__ is_null_oid (struct object_id const*) ; 
 scalar_t__ memcmp (char const*,char const*,int) ; 
 char* oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  oidcpy (struct object_id const*,struct object_id const*) ; 
 scalar_t__ repository_format_partial_clone ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,unsigned int,int,char const*,char) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 char* strchr (char const*,char) ; 
 TYPE_2__* the_hash_algo ; 
 int /*<<< orphan*/  tree_type ; 
 scalar_t__ write_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id const*) ; 

__attribute__((used)) static int update_one(struct cache_tree *it,
		      struct cache_entry **cache,
		      int entries,
		      const char *base,
		      int baselen,
		      int *skip_count,
		      int flags)
{
	struct strbuf buffer;
	int missing_ok = flags & WRITE_TREE_MISSING_OK;
	int dryrun = flags & WRITE_TREE_DRY_RUN;
	int repair = flags & WRITE_TREE_REPAIR;
	int to_invalidate = 0;
	int i;

	assert(!(dryrun && repair));

	*skip_count = 0;

	if (0 <= it->entry_count && has_object_file(&it->oid))
		return it->entry_count;

	/*
	 * We first scan for subtrees and update them; we start by
	 * marking existing subtrees -- the ones that are unmarked
	 * should not be in the result.
	 */
	for (i = 0; i < it->subtree_nr; i++)
		it->down[i]->used = 0;

	/*
	 * Find the subtrees and update them.
	 */
	i = 0;
	while (i < entries) {
		const struct cache_entry *ce = cache[i];
		struct cache_tree_sub *sub;
		const char *path, *slash;
		int pathlen, sublen, subcnt, subskip;

		path = ce->name;
		pathlen = ce_namelen(ce);
		if (pathlen <= baselen || memcmp(base, path, baselen))
			break; /* at the end of this level */

		slash = strchr(path + baselen, '/');
		if (!slash) {
			i++;
			continue;
		}
		/*
		 * a/bbb/c (base = a/, slash = /c)
		 * ==>
		 * path+baselen = bbb/c, sublen = 3
		 */
		sublen = slash - (path + baselen);
		sub = find_subtree(it, path + baselen, sublen, 1);
		if (!sub->cache_tree)
			sub->cache_tree = cache_tree();
		subcnt = update_one(sub->cache_tree,
				    cache + i, entries - i,
				    path,
				    baselen + sublen + 1,
				    &subskip,
				    flags);
		if (subcnt < 0)
			return subcnt;
		if (!subcnt)
			die("index cache-tree records empty sub-tree");
		i += subcnt;
		sub->count = subcnt; /* to be used in the next loop */
		*skip_count += subskip;
		sub->used = 1;
	}

	discard_unused_subtrees(it);

	/*
	 * Then write out the tree object for this level.
	 */
	strbuf_init(&buffer, 8192);

	i = 0;
	while (i < entries) {
		const struct cache_entry *ce = cache[i];
		struct cache_tree_sub *sub = NULL;
		const char *path, *slash;
		int pathlen, entlen;
		const struct object_id *oid;
		unsigned mode;
		int expected_missing = 0;
		int contains_ita = 0;
		int ce_missing_ok;

		path = ce->name;
		pathlen = ce_namelen(ce);
		if (pathlen <= baselen || memcmp(base, path, baselen))
			break; /* at the end of this level */

		slash = strchr(path + baselen, '/');
		if (slash) {
			entlen = slash - (path + baselen);
			sub = find_subtree(it, path + baselen, entlen, 0);
			if (!sub)
				die("cache-tree.c: '%.*s' in '%s' not found",
				    entlen, path + baselen, path);
			i += sub->count;
			oid = &sub->cache_tree->oid;
			mode = S_IFDIR;
			contains_ita = sub->cache_tree->entry_count < 0;
			if (contains_ita) {
				to_invalidate = 1;
				expected_missing = 1;
			}
		}
		else {
			oid = &ce->oid;
			mode = ce->ce_mode;
			entlen = pathlen - baselen;
			i++;
		}

		ce_missing_ok = mode == S_IFGITLINK || missing_ok ||
			(repository_format_partial_clone &&
			 ce_skip_worktree(ce));
		if (is_null_oid(oid) ||
		    (!ce_missing_ok && !has_object_file(oid))) {
			strbuf_release(&buffer);
			if (expected_missing)
				return -1;
			return error("invalid object %06o %s for '%.*s'",
				mode, oid_to_hex(oid), entlen+baselen, path);
		}

		/*
		 * CE_REMOVE entries are removed before the index is
		 * written to disk. Skip them to remain consistent
		 * with the future on-disk index.
		 */
		if (ce->ce_flags & CE_REMOVE) {
			*skip_count = *skip_count + 1;
			continue;
		}

		/*
		 * CE_INTENT_TO_ADD entries exist on on-disk index but
		 * they are not part of generated trees. Invalidate up
		 * to root to force cache-tree users to read elsewhere.
		 */
		if (!sub && ce_intent_to_add(ce)) {
			to_invalidate = 1;
			continue;
		}

		/*
		 * "sub" can be an empty tree if all subentries are i-t-a.
		 */
		if (contains_ita && is_empty_tree_oid(oid))
			continue;

		strbuf_grow(&buffer, entlen + 100);
		strbuf_addf(&buffer, "%o %.*s%c", mode, entlen, path + baselen, '\0');
		strbuf_add(&buffer, oid->hash, the_hash_algo->rawsz);

#if DEBUG
		fprintf(stderr, "cache-tree update-one %o %.*s\n",
			mode, entlen, path + baselen);
#endif
	}

	if (repair) {
		struct object_id oid;
		hash_object_file(buffer.buf, buffer.len, tree_type, &oid);
		if (has_object_file(&oid))
			oidcpy(&it->oid, &oid);
		else
			to_invalidate = 1;
	} else if (dryrun) {
		hash_object_file(buffer.buf, buffer.len, tree_type, &it->oid);
	} else if (write_object_file(buffer.buf, buffer.len, tree_type,
				     &it->oid)) {
		strbuf_release(&buffer);
		return -1;
	}

	strbuf_release(&buffer);
	it->entry_count = to_invalidate ? -1 : i - *skip_count;
#if DEBUG
	fprintf(stderr, "cache-tree update-one (%d ent, %d subtree) %s\n",
		it->entry_count, it->subtree_nr,
		oid_to_hex(&it->oid));
#endif
	return i;
}