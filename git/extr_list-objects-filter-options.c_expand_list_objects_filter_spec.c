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
struct list_objects_filter_options {scalar_t__ choice; int /*<<< orphan*/  filter_spec; int /*<<< orphan*/  blob_limit_value; } ;

/* Variables and functions */
 scalar_t__ LOFC_BLOB_LIMIT ; 
 struct strbuf STRBUF_INIT ; 
 char const* list_objects_filter_spec (struct list_objects_filter_options*) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

const char *expand_list_objects_filter_spec(
	struct list_objects_filter_options *filter)
{
	if (filter->choice == LOFC_BLOB_LIMIT) {
		struct strbuf expanded_spec = STRBUF_INIT;
		strbuf_addf(&expanded_spec, "blob:limit=%lu",
			    filter->blob_limit_value);
		string_list_clear(&filter->filter_spec, /*free_util=*/0);
		string_list_append(
			&filter->filter_spec,
			strbuf_detach(&expanded_spec, NULL));
	}

	return list_objects_filter_spec(filter);
}