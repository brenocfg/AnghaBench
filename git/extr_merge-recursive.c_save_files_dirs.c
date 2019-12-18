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
struct path_hashmap_entry {int /*<<< orphan*/  e; int /*<<< orphan*/  path; } ;
struct object_id {int dummy; } ;
struct merge_options {TYPE_1__* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  current_file_dir_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ALLOC_MEM (struct path_hashmap_entry*,char const*,int /*<<< orphan*/ ,int) ; 
 int READ_TREE_RECURSIVE ; 
 scalar_t__ S_ISDIR (unsigned int) ; 
 int /*<<< orphan*/  hashmap_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_entry_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_setlen (struct strbuf*,int) ; 

__attribute__((used)) static int save_files_dirs(const struct object_id *oid,
			   struct strbuf *base, const char *path,
			   unsigned int mode, int stage, void *context)
{
	struct path_hashmap_entry *entry;
	int baselen = base->len;
	struct merge_options *opt = context;

	strbuf_addstr(base, path);

	FLEX_ALLOC_MEM(entry, path, base->buf, base->len);
	hashmap_entry_init(&entry->e, path_hash(entry->path));
	hashmap_add(&opt->priv->current_file_dir_set, &entry->e);

	strbuf_setlen(base, baselen);
	return (S_ISDIR(mode) ? READ_TREE_RECURSIVE : 0);
}