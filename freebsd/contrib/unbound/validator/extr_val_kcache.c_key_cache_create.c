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
struct key_cache {int /*<<< orphan*/  slab; } ;
struct config_file {size_t key_cache_slabs; size_t key_cache_size; } ;

/* Variables and functions */
 size_t HASH_DEFAULT_STARTARRAY ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (struct key_cache*) ; 
 int /*<<< orphan*/  key_entry_compfunc ; 
 int /*<<< orphan*/  key_entry_deldatafunc ; 
 int /*<<< orphan*/  key_entry_delkeyfunc ; 
 int /*<<< orphan*/  key_entry_sizefunc ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  slabhash_create (size_t,size_t,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct key_cache* 
key_cache_create(struct config_file* cfg)
{
	struct key_cache* kcache = (struct key_cache*)calloc(1, 
		sizeof(*kcache));
	size_t numtables, start_size, maxmem;
	if(!kcache) {
		log_err("malloc failure");
		return NULL;
	}
	numtables = cfg->key_cache_slabs;
	start_size = HASH_DEFAULT_STARTARRAY;
	maxmem = cfg->key_cache_size;
	kcache->slab = slabhash_create(numtables, start_size, maxmem,
		&key_entry_sizefunc, &key_entry_compfunc,
		&key_entry_delkeyfunc, &key_entry_deldatafunc, NULL);
	if(!kcache->slab) {
		log_err("malloc failure");
		free(kcache);
		return NULL;
	}
	return kcache;
}