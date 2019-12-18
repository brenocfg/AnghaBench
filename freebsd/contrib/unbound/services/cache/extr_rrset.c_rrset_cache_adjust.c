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
struct rrset_cache {int /*<<< orphan*/  table; } ;
struct config_file {int /*<<< orphan*/  rrset_cache_slabs; int /*<<< orphan*/  rrset_cache_size; } ;
struct alloc_cache {int dummy; } ;

/* Variables and functions */
 struct rrset_cache* rrset_cache_create (struct config_file*,struct alloc_cache*) ; 
 int /*<<< orphan*/  rrset_cache_delete (struct rrset_cache*) ; 
 int /*<<< orphan*/  slabhash_is_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

struct rrset_cache* rrset_cache_adjust(struct rrset_cache *r, 
	struct config_file* cfg, struct alloc_cache* alloc)
{
	if(!r || !cfg || !slabhash_is_size(&r->table, cfg->rrset_cache_size,
		cfg->rrset_cache_slabs))
	{
		rrset_cache_delete(r);
		r = rrset_cache_create(cfg, alloc);
	}
	return r;
}