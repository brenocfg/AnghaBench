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
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_add_entry (struct unpack_trees_options*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dup_cache_entry (struct cache_entry const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void add_entry(struct unpack_trees_options *o,
		      const struct cache_entry *ce,
		      unsigned int set, unsigned int clear)
{
	do_add_entry(o, dup_cache_entry(ce, &o->result), set, clear);
}