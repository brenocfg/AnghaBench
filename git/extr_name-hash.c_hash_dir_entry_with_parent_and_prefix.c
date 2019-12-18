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
struct strbuf {scalar_t__ len; scalar_t__ buf; } ;
struct index_state {int /*<<< orphan*/  dir_hash; } ;
struct TYPE_3__ {unsigned int hash; } ;
struct dir_entry {int /*<<< orphan*/  nr; TYPE_1__ ent; struct dir_entry* parent; scalar_t__ namelen; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_MEM (struct dir_entry*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int compute_dir_lock_nr (int /*<<< orphan*/ *,unsigned int) ; 
 struct dir_entry* find_dir_entry__hash (struct index_state*,scalar_t__,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  hashmap_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  hashmap_entry_init (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  lock_dir_mutex (int) ; 
 unsigned int memihash (scalar_t__,scalar_t__) ; 
 unsigned int memihash_cont (unsigned int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/ * strchr (scalar_t__,char) ; 
 int /*<<< orphan*/  unlock_dir_mutex (int) ; 

__attribute__((used)) static struct dir_entry *hash_dir_entry_with_parent_and_prefix(
	struct index_state *istate,
	struct dir_entry *parent,
	struct strbuf *prefix)
{
	struct dir_entry *dir;
	unsigned int hash;
	int lock_nr;

	/*
	 * Either we have a parent directory and path with slash(es)
	 * or the directory is an immediate child of the root directory.
	 */
	assert((parent != NULL) ^ (strchr(prefix->buf, '/') == NULL));

	if (parent)
		hash = memihash_cont(parent->ent.hash,
			prefix->buf + parent->namelen,
			prefix->len - parent->namelen);
	else
		hash = memihash(prefix->buf, prefix->len);

	lock_nr = compute_dir_lock_nr(&istate->dir_hash, hash);
	lock_dir_mutex(lock_nr);

	dir = find_dir_entry__hash(istate, prefix->buf, prefix->len, hash);
	if (!dir) {
		FLEX_ALLOC_MEM(dir, name, prefix->buf, prefix->len);
		hashmap_entry_init(&dir->ent, hash);
		dir->namelen = prefix->len;
		dir->parent = parent;
		hashmap_add(&istate->dir_hash, &dir->ent);

		if (parent) {
			unlock_dir_mutex(lock_nr);

			/* All I really need here is an InterlockedIncrement(&(parent->nr)) */
			lock_nr = compute_dir_lock_nr(&istate->dir_hash, parent->ent.hash);
			lock_dir_mutex(lock_nr);
			parent->nr++;
		}
	}

	unlock_dir_mutex(lock_nr);

	return dir;
}