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
struct index_state {int dummy; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  find_mem_pool (struct index_state*) ; 
 struct cache_entry* mem_pool__ce_calloc (int /*<<< orphan*/ ,size_t) ; 

struct cache_entry *make_empty_cache_entry(struct index_state *istate, size_t len)
{
	return mem_pool__ce_calloc(find_mem_pool(istate), len);
}