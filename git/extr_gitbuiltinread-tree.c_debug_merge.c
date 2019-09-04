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
struct unpack_trees_options {int merge_size; } ;
struct cache_entry {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  debug_stage (char*,struct cache_entry const* const,struct unpack_trees_options*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,int) ; 

__attribute__((used)) static int debug_merge(const struct cache_entry * const *stages,
		       struct unpack_trees_options *o)
{
	int i;

	printf("* %d-way merge\n", o->merge_size);
	debug_stage("index", stages[0], o);
	for (i = 1; i <= o->merge_size; i++) {
		char buf[24];
		xsnprintf(buf, sizeof(buf), "ent#%d", i);
		debug_stage(buf, stages[i], o);
	}
	return 0;
}