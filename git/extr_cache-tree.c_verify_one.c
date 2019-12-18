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
struct strbuf {int len; int /*<<< orphan*/  buf; } ;
struct repository {int dummy; } ;
struct object_id {int /*<<< orphan*/  hash; } ;
struct index_state {struct cache_entry** cache; } ;
struct cache_tree_sub {TYPE_2__* cache_tree; } ;
struct cache_tree {int subtree_nr; int entry_count; struct object_id oid; TYPE_1__** down; } ;
struct cache_entry {int ce_flags; char* name; unsigned int ce_mode; struct object_id oid; } ;
struct TYPE_6__ {int /*<<< orphan*/  rawsz; } ;
struct TYPE_5__ {scalar_t__ entry_count; struct object_id oid; } ;
struct TYPE_4__ {struct cache_tree* cache_tree; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,...) ; 
 int CE_INTENT_TO_ADD ; 
 int CE_REMOVE ; 
 int CE_STAGEMASK ; 
 struct strbuf STRBUF_INIT ; 
 unsigned int S_IFDIR ; 
 int ce_namelen (struct cache_entry*) ; 
 struct cache_tree_sub* find_subtree (struct cache_tree*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_object_file (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct object_id*) ; 
 int index_name_pos (struct index_state*,int /*<<< orphan*/ ,int) ; 
 struct object_id* lookup_replace_object (struct repository*,struct object_id*) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id*) ; 
 int /*<<< orphan*/  oideq (struct object_id*,struct object_id*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,unsigned int,...) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 char* strchr (char const*,char) ; 
 TYPE_3__* the_hash_algo ; 
 int /*<<< orphan*/  tree_type ; 

__attribute__((used)) static void verify_one(struct repository *r,
		       struct index_state *istate,
		       struct cache_tree *it,
		       struct strbuf *path)
{
	int i, pos, len = path->len;
	struct strbuf tree_buf = STRBUF_INIT;
	struct object_id new_oid;

	for (i = 0; i < it->subtree_nr; i++) {
		strbuf_addf(path, "%s/", it->down[i]->name);
		verify_one(r, istate, it->down[i]->cache_tree, path);
		strbuf_setlen(path, len);
	}

	if (it->entry_count < 0 ||
	    /* no verification on tests (t7003) that replace trees */
	    lookup_replace_object(r, &it->oid) != &it->oid)
		return;

	if (path->len) {
		pos = index_name_pos(istate, path->buf, path->len);
		pos = -pos - 1;
	} else {
		pos = 0;
	}

	i = 0;
	while (i < it->entry_count) {
		struct cache_entry *ce = istate->cache[pos + i];
		const char *slash;
		struct cache_tree_sub *sub = NULL;
		const struct object_id *oid;
		const char *name;
		unsigned mode;
		int entlen;

		if (ce->ce_flags & (CE_STAGEMASK | CE_INTENT_TO_ADD | CE_REMOVE))
			BUG("%s with flags 0x%x should not be in cache-tree",
			    ce->name, ce->ce_flags);
		name = ce->name + path->len;
		slash = strchr(name, '/');
		if (slash) {
			entlen = slash - name;
			sub = find_subtree(it, ce->name + path->len, entlen, 0);
			if (!sub || sub->cache_tree->entry_count < 0)
				BUG("bad subtree '%.*s'", entlen, name);
			oid = &sub->cache_tree->oid;
			mode = S_IFDIR;
			i += sub->cache_tree->entry_count;
		} else {
			oid = &ce->oid;
			mode = ce->ce_mode;
			entlen = ce_namelen(ce) - path->len;
			i++;
		}
		strbuf_addf(&tree_buf, "%o %.*s%c", mode, entlen, name, '\0');
		strbuf_add(&tree_buf, oid->hash, the_hash_algo->rawsz);
	}
	hash_object_file(tree_buf.buf, tree_buf.len, tree_type, &new_oid);
	if (!oideq(&new_oid, &it->oid))
		BUG("cache-tree for path %.*s does not match. "
		    "Expected %s got %s", len, path->buf,
		    oid_to_hex(&new_oid), oid_to_hex(&it->oid));
	strbuf_setlen(path, len);
	strbuf_release(&tree_buf);
}