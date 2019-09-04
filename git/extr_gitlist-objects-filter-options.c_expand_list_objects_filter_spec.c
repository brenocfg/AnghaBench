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
struct strbuf {int dummy; } ;
struct list_objects_filter_options {scalar_t__ choice; int /*<<< orphan*/  filter_spec; int /*<<< orphan*/  tree_exclude_depth; int /*<<< orphan*/  blob_limit_value; } ;

/* Variables and functions */
 scalar_t__ LOFC_BLOB_LIMIT ; 
 scalar_t__ LOFC_TREE_DEPTH ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_init (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void expand_list_objects_filter_spec(
	const struct list_objects_filter_options *filter,
	struct strbuf *expanded_spec)
{
	strbuf_init(expanded_spec, strlen(filter->filter_spec));
	if (filter->choice == LOFC_BLOB_LIMIT)
		strbuf_addf(expanded_spec, "blob:limit=%lu",
			    filter->blob_limit_value);
	else if (filter->choice == LOFC_TREE_DEPTH)
		strbuf_addf(expanded_spec, "tree:%lu",
			    filter->tree_exclude_depth);
	else
		strbuf_addstr(expanded_spec, filter->filter_spec);
}