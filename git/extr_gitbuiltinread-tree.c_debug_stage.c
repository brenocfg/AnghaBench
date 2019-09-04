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
struct unpack_trees_options {struct cache_entry const* df_conflict_entry; } ;
struct cache_entry {int ce_mode; char* name; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int ce_stage (struct cache_entry const*) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void debug_stage(const char *label, const struct cache_entry *ce,
			struct unpack_trees_options *o)
{
	printf("%s ", label);
	if (!ce)
		printf("(missing)\n");
	else if (ce == o->df_conflict_entry)
		printf("(conflict)\n");
	else
		printf("%06o #%d %s %.8s\n",
		       ce->ce_mode, ce_stage(ce), ce->name,
		       oid_to_hex(&ce->oid));
}