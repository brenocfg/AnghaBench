#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct merge_options {TYPE_1__* priv; } ;
struct diff_filespec {scalar_t__ mode; int /*<<< orphan*/  oid; } ;
struct cache_entry {scalar_t__ ce_mode; int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {struct cache_entry** cache; } ;
struct TYPE_3__ {TYPE_2__ orig_index; } ;

/* Variables and functions */
 int index_name_pos (TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ oid_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int was_tracked_and_matches(struct merge_options *opt, const char *path,
				   const struct diff_filespec *blob)
{
	int pos = index_name_pos(&opt->priv->orig_index, path, strlen(path));
	struct cache_entry *ce;

	if (0 > pos)
		/* we were not tracking this path before the merge */
		return 0;

	/* See if the file we were tracking before matches */
	ce = opt->priv->orig_index.cache[pos];
	return (oid_eq(&ce->oid, &blob->oid) && ce->ce_mode == blob->mode);
}