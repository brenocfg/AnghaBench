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
struct unpack_trees_options {int /*<<< orphan*/  result; } ;
struct cache_entry {unsigned int ce_flags; } ;

/* Variables and functions */
 int ADD_CACHE_OK_TO_ADD ; 
 int ADD_CACHE_OK_TO_REPLACE ; 
 unsigned int CE_HASHED ; 
 unsigned int CE_REMOVE ; 
 unsigned int CE_WT_REMOVE ; 
 int add_index_entry (int /*<<< orphan*/ *,struct cache_entry*,int) ; 

__attribute__((used)) static int do_add_entry(struct unpack_trees_options *o, struct cache_entry *ce,
			 unsigned int set, unsigned int clear)
{
	clear |= CE_HASHED;

	if (set & CE_REMOVE)
		set |= CE_WT_REMOVE;

	ce->ce_flags = (ce->ce_flags & ~clear) | set;
	return add_index_entry(&o->result, ce,
			       ADD_CACHE_OK_TO_ADD | ADD_CACHE_OK_TO_REPLACE);
}