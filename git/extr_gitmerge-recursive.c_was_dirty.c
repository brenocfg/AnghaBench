#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  src_index; } ;
struct merge_options {TYPE_1__ unpack_opts; scalar_t__ call_depth; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ignore_case ; 
 struct cache_entry* index_file_exists (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 scalar_t__ verify_uptodate (struct cache_entry*,TYPE_1__*) ; 
 int /*<<< orphan*/  was_tracked (struct merge_options*,char const*) ; 

__attribute__((used)) static int was_dirty(struct merge_options *o, const char *path)
{
	struct cache_entry *ce;
	int dirty = 1;

	if (o->call_depth || !was_tracked(o, path))
		return !dirty;

	ce = index_file_exists(o->unpack_opts.src_index,
			       path, strlen(path), ignore_case);
	dirty = verify_uptodate(ce, &o->unpack_opts) != 0;
	return dirty;
}