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
struct strbuf {int len; int /*<<< orphan*/  buf; } ;
struct lazy_entry {int /*<<< orphan*/  hash_name; int /*<<< orphan*/  hash_dir; struct dir_entry* dir; } ;
struct index_state {struct cache_entry** cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash; } ;
struct dir_entry {int namelen; TYPE_1__ ent; } ;
struct cache_entry {char* name; } ;

/* Variables and functions */
 int ce_namelen (struct cache_entry*) ; 
 int handle_range_dir (struct index_state*,int,int,struct dir_entry*,struct strbuf*,struct lazy_entry*,struct dir_entry**) ; 
 int /*<<< orphan*/  memihash (char*,int) ; 
 int /*<<< orphan*/  memihash_cont (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int handle_range_1(
	struct index_state *istate,
	int k_start,
	int k_end,
	struct dir_entry *parent,
	struct strbuf *prefix,
	struct lazy_entry *lazy_entries)
{
	int input_prefix_len = prefix->len;
	int k = k_start;

	while (k < k_end) {
		struct cache_entry *ce_k = istate->cache[k];
		const char *name, *slash;

		if (prefix->len && strncmp(ce_k->name, prefix->buf, prefix->len))
			break;

		name = ce_k->name + prefix->len;
		slash = strchr(name, '/');

		if (slash) {
			int len = slash - name;
			int processed;
			struct dir_entry *dir_new;

			strbuf_add(prefix, name, len);
			processed = handle_range_dir(istate, k, k_end, parent, prefix, lazy_entries, &dir_new);
			if (processed) {
				k += processed;
				strbuf_setlen(prefix, input_prefix_len);
				continue;
			}

			strbuf_addch(prefix, '/');
			processed = handle_range_1(istate, k, k_end, dir_new, prefix, lazy_entries);
			k += processed;
			strbuf_setlen(prefix, input_prefix_len);
			continue;
		}

		/*
		 * It is too expensive to take a lock to insert "ce_k"
		 * into "istate->name_hash" and increment the ref-count
		 * on the "parent" dir.  So we defer actually updating
		 * permanent data structures until phase 2 (where we
		 * can change the locking requirements) and simply
		 * accumulate our current results into the lazy_entries
		 * data array).
		 *
		 * We do not need to lock the lazy_entries array because
		 * we have exclusive access to the cells in the range
		 * [k_start,k_end) that this thread was given.
		 */
		lazy_entries[k].dir = parent;
		if (parent) {
			lazy_entries[k].hash_name = memihash_cont(
				parent->ent.hash,
				ce_k->name + parent->namelen,
				ce_namelen(ce_k) - parent->namelen);
			lazy_entries[k].hash_dir = parent->ent.hash;
		} else {
			lazy_entries[k].hash_name = memihash(ce_k->name, ce_namelen(ce_k));
		}

		k++;
	}

	return k - k_start;
}