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
struct mem_pool {int dummy; } ;
struct cache_entry {int mem_pool_allocated; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_entry_size (size_t) ; 
 struct cache_entry* mem_pool_calloc (struct mem_pool*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct cache_entry *mem_pool__ce_calloc(struct mem_pool *mem_pool, size_t len)
{
	struct cache_entry * ce;
	ce = mem_pool_calloc(mem_pool, 1, cache_entry_size(len));
	ce->mem_pool_allocated = 1;
	return ce;
}