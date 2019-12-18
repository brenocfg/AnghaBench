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
struct list_objects_filter_options {scalar_t__ choice; int sub_alloc; int sub_nr; int /*<<< orphan*/  filter_spec; struct list_objects_filter_options* sub; } ;

/* Variables and functions */
 scalar_t__ LOFC_COMBINE ; 
 int /*<<< orphan*/  assert (scalar_t__) ; 
 int /*<<< orphan*/  filter_spec_append_urlencode (struct list_objects_filter_options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_objects_filter_spec (struct list_objects_filter_options*) ; 
 int /*<<< orphan*/  memset (struct list_objects_filter_options*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  string_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct list_objects_filter_options* xcalloc (int const,int) ; 
 int /*<<< orphan*/  xstrdup (char*) ; 

__attribute__((used)) static void transform_to_combine_type(
	struct list_objects_filter_options *filter_options)
{
	assert(filter_options->choice);
	if (filter_options->choice == LOFC_COMBINE)
		return;
	{
		const int initial_sub_alloc = 2;
		struct list_objects_filter_options *sub_array =
			xcalloc(initial_sub_alloc, sizeof(*sub_array));
		sub_array[0] = *filter_options;
		memset(filter_options, 0, sizeof(*filter_options));
		filter_options->sub = sub_array;
		filter_options->sub_alloc = initial_sub_alloc;
	}
	filter_options->sub_nr = 1;
	filter_options->choice = LOFC_COMBINE;
	string_list_append(&filter_options->filter_spec, xstrdup("combine:"));
	filter_spec_append_urlencode(
		filter_options,
		list_objects_filter_spec(&filter_options->sub[0]));
	/*
	 * We don't need the filter_spec strings for subfilter specs, only the
	 * top level.
	 */
	string_list_clear(&filter_options->sub[0].filter_spec, /*free_util=*/0);
}