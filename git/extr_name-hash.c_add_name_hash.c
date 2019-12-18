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
struct index_state {scalar_t__ name_hash_initialized; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_index_entry (struct index_state*,struct cache_entry*) ; 

void add_name_hash(struct index_state *istate, struct cache_entry *ce)
{
	if (istate->name_hash_initialized)
		hash_index_entry(istate, ce);
}