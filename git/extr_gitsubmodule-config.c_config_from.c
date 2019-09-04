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
struct submodule_entry {struct submodule const* config; } ;
struct submodule_cache {int /*<<< orphan*/  for_name; } ;
struct submodule {int dummy; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct parse_config_parameter {scalar_t__ overwrite; struct object_id* gitmodules_oid; struct object_id const* treeish_name; struct submodule_cache* cache; } ;
struct object_id {int dummy; } ;
struct hashmap_iter {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
typedef  enum lookup_type { ____Placeholder_lookup_type } lookup_type ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ORIGIN_SUBMODULE_BLOB ; 
 int OBJ_BLOB ; 
 struct strbuf STRBUF_INIT ; 
 struct submodule const* cache_lookup_name (struct submodule_cache*,struct object_id*,char const*) ; 
 struct submodule const* cache_lookup_path (struct submodule_cache*,struct object_id*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  git_config_from_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned long,struct parse_config_parameter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gitmodule_oid_from_commit (struct object_id const*,struct object_id*,struct strbuf*) ; 
 struct submodule_entry* hashmap_iter_first (int /*<<< orphan*/ *,struct hashmap_iter*) ; 
#define  lookup_name 129 
#define  lookup_path 128 
 int /*<<< orphan*/  parse_config ; 
 char* read_object_file (struct object_id*,int*,unsigned long*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static const struct submodule *config_from(struct submodule_cache *cache,
		const struct object_id *treeish_name, const char *key,
		enum lookup_type lookup_type)
{
	struct strbuf rev = STRBUF_INIT;
	unsigned long config_size;
	char *config = NULL;
	struct object_id oid;
	enum object_type type;
	const struct submodule *submodule = NULL;
	struct parse_config_parameter parameter;

	/*
	 * If any parameter except the cache is a NULL pointer just
	 * return the first submodule. Can be used to check whether
	 * there are any submodules parsed.
	 */
	if (!treeish_name || !key) {
		struct hashmap_iter iter;
		struct submodule_entry *entry;

		entry = hashmap_iter_first(&cache->for_name, &iter);
		if (!entry)
			return NULL;
		return entry->config;
	}

	if (!gitmodule_oid_from_commit(treeish_name, &oid, &rev))
		goto out;

	switch (lookup_type) {
	case lookup_name:
		submodule = cache_lookup_name(cache, &oid, key);
		break;
	case lookup_path:
		submodule = cache_lookup_path(cache, &oid, key);
		break;
	}
	if (submodule)
		goto out;

	config = read_object_file(&oid, &type, &config_size);
	if (!config || type != OBJ_BLOB)
		goto out;

	/* fill the submodule config into the cache */
	parameter.cache = cache;
	parameter.treeish_name = treeish_name;
	parameter.gitmodules_oid = &oid;
	parameter.overwrite = 0;
	git_config_from_mem(parse_config, CONFIG_ORIGIN_SUBMODULE_BLOB, rev.buf,
			config, config_size, &parameter, NULL);
	strbuf_release(&rev);
	free(config);

	switch (lookup_type) {
	case lookup_name:
		return cache_lookup_name(cache, &oid, key);
	case lookup_path:
		return cache_lookup_path(cache, &oid, key);
	default:
		return NULL;
	}

out:
	strbuf_release(&rev);
	free(config);
	return submodule;
}